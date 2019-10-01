#include <iostream>
#include <algorithm>
#include <queue>

#include "grafo.hpp"

#define INF 0x3f3f3f3f

Grafo::Grafo() {

}

Grafo::Grafo(int V, std::vector<Vertice *> vertices, bool orientado) {
   this->vertices = vertices; 
   this->orientado = orientado;
   this->V = V;
   this->E = 0;
   adj = new std::vector<Link *>[V];
}

void Grafo::addAresta(Aresta *aresta) {
   int u = aresta->getU()->getId();
   int v = aresta->getV()->getId();
   int peso = aresta->getPeso();
   std::string label = aresta->getLabel();

   adj[u].push_back(new Link(label, peso, v));
   if (!orientado) {
      adj[v].push_back(new Link(label, peso, u));
   }
   ++E;
}

std::vector<ii> Grafo::dfs(int u) {
   std::vector<ii> res;
   bool *visitado = new bool[V];
   for (size_t i = 0; i < V; ++i) {
      visitado[i] = false;
   }

   for (size_t i = 0; i < V; ++i) {
      if (!visitado[i]) {
         dfsVisit(u, visitado, res);
      }
   }
   delete visitado;
   return res;
}

void Grafo::dfsVisit(int u, bool *visitado, 
std::vector<ii> &res) {
   visitado[u] = true;
   for (auto it : adj[u]) {
      int v = it->v;
      if (!visitado[v]) {
         res.push_back({u, v});
         dfsVisit(v, visitado, res);
      }
   }
}

std::vector<ii> Grafo::bfs(int s) {
   std::vector<ii> res;
   bool *visitado = new bool[V];
   for (size_t i = 0; i < V; ++i) {
      visitado[i] = false;
   }
   visitado[s] = true;

   std::queue<int> q;
   q.push(s);
   while (!q.empty()) {
      int u = q.front();
      for (auto it : adj[u]) {
         int v = it->v;
         if (!visitado[v]) {
            visitado[v] = true;
            q.push(v);
            res.push_back({u, v});
         }
      }
      q.pop();
   }
   delete [] visitado;
   return res;
}

std::vector<int> Grafo::bFord(int src) {
   std::vector<int> dist(V);
   for (size_t i = 0; i < V; ++i) {
      dist[i] = INF;
   }
   dist[src] = 0;

   for (int i = 0; i < V - 1; ++i) {
      for (size_t j = 0; j < V; ++j) {
         for (auto it : adj[j]) {
            dist[it->v] = std::min(dist[j] + it->peso, dist[it->v]);
         }
      }
   }

   for (size_t j = 0; j < V; ++j) {
      for (auto it : adj[j]) {
         if (dist[j] + it->peso < dist[it->v]) {
            dist[it->v] = -INF;
         }
      }
   }
   return dist;
}

std::vector<ii> Grafo::kruskal(int &custo) {
   std::vector<Aresta *> arestas = toArestas();
   std::vector<ii> mst;
   std::sort(arestas.begin(), arestas.end(), Aresta::comp);

   int pai[V]; //union-find
   for (int i = 0; i < V; ++i) {
      pai[i] = i;
   }

   for (int i = custo = 0; i < arestas.size(); ++i) {
      Aresta *aresta = arestas[i];
      int pa = findset(pai, aresta->getU()->getId());
      int pb = findset(pai, aresta->getV()->getId());

      //se n estao no msm conjunto, adicionamos a aresta e n ira formar ciclo
      if (pa != pb) { 
         custo += aresta->getPeso();
         pai[pa] = pb;
         mst.push_back({aresta->getU()->getId(), aresta->getV()->getId()});
      }
   }
   return mst;
}

int Grafo::findset(int v[], int x) {
   if (x != v[x])
      v[x] = findset(v, v[x]);
   return v[x];
}

std::vector<ii> Grafo::prim(int src, int &custo) {
   std::vector<ii> res;
   std::priority_queue<ii, std::vector<ii>, std::greater<ii>> pq;
   std::vector<int> key(V, INF);
   std::vector<int> pai(V, -1);
   std::vector<bool> inMST(V, false); //vertices inclusos na MST

   pq.push({0, src}); //chave do vertice inicial sera 0
   
   while (!pq.empty()) {
      int u = pq.top().second; pq.pop();
      inMST[u] = true;
      for (auto it : adj[u]) {
         int v = it->v;
         int w = it->peso;
         if (!inMST[v] && key[v] > w) {
            key[v] = w;
            pq.push({key[v], v});
            pai[v] = u;
         }
      }
   }
   for (int i = 1; i < V; ++i) {
      res.push_back({pai[i], i});
   }
   return res;
}

bool Grafo::comp(Link *a, Link *b) {
   return (a->v < b->v);
}

void Grafo::sort() {
   for (size_t i = 0; i < V; ++i) {
      std::sort(adj[i].begin(), adj[i].end(), Grafo::comp);
   }
}

std::vector<Aresta *> Grafo::toArestas() {
   std::vector<Aresta *> arestas;
   for (size_t i = 0; i < V; ++i) {
      for (auto it : adj[i]) {
         int v = it->v;
         int w = it->peso;
         if (i <= v)  {
            arestas.push_back(new Aresta(w, new Vertice(i), new Vertice(v)));
         }
      }
   }
   return arestas;
}

//debug
void Grafo::show() const {
   for (size_t i = 0; i < V; ++i) {
      std::cout << "V[" << i << "]:" << std::endl;
      for (auto it : adj[i]) {
         std::cout << "" << it->v << std::endl;
      }
   }
}

Grafo::~Grafo() {
   for (size_t i = 0; i < V; ++i) {
      for (auto it : adj[i]) {
         delete it; it = nullptr;
      }
   }
   delete [] adj; adj = nullptr;
}