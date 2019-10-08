#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>

#include "grafo.hpp"

#define INF 0x3f3f3f3f

Grafo::Grafo() {
   this->V = 0;
   this->E = 0;
   adj = nullptr;
}

Grafo::Grafo(int V, std::vector<Vertice *> vertices, bool orientado) {
   this->vertices = vertices; 
   this->orientado = orientado;
   this->V = V;
   this->E = 0;
   adj = new std::vector<Link *>[V];
}

//copy constructor (sem os vertices)
Grafo::Grafo(Grafo &other) {
   this->V = other.getNumV();
   this->E = other.getNumE();
   this->orientado = other.isOrientado();
   this->adj = new std::vector<Link *>[V];
   for (size_t i = 0; i < V; ++i) {
      for (size_t j = 0; j < other.getAdj()[i].size(); ++j) {
         Link *v = other.getAdj()[i][j];
         adj[i].push_back(new Link(v->label, v->peso, v->v));
      }
   }
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

int Grafo::getNumV() const {
   return V;
}

int Grafo::getNumE() const {
   return E;
}

std::vector<Link *> *Grafo::getAdj() {
   return adj;
}

std::vector<Vertice *> Grafo::getVertices() {
   return vertices;
}

std::string Grafo::getLabelVertice(int u) {
   if (vertices[u]->getLabel() == "") {
      return std::to_string(vertices[u]->getId());
   }
   return vertices[u]->getLabel();
}

bool Grafo::isOrientado() const {
   return orientado;
}

std::vector<ii> Grafo::dfs(int src) {
   std::vector<ii> res;
   bool *visitado = new bool[V];
   memset(visitado, false, sizeof(visitado));
   dfsVisit(src, visitado, res);
   delete [] visitado;
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

std::vector<ii> Grafo::bfs(int src) {
   std::vector<ii> res;
   bool *visitado = new bool[V];
   for (size_t i = 0; i < V; ++i) {
      visitado[i] = false;
   }
   visitado[src] = true;

   std::queue<int> q;
   q.push(src);
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

bool Grafo::bellmanFord(int src, std::vector<ii> &caminhos, 
std::vector<int> &custo) {
   std::vector<int> dist(V);
   std::vector<int> pred(V);
   for (size_t i = 0; i < V; ++i) {
      dist[i] = INF;
      pred[i] = -1;
   }
   dist[src] = 0;

   for (int i = 0; i < V - 1; ++i) {
      for (size_t u = 0; u < V; ++u) {
         for (auto it : adj[u]) {
            //relax, apenas faz sentido se dist[u] != INF
            //pois INFINITO + (numeroNegativo) = INFINITO
            if (dist[u] != INF && dist[u] + it->peso < dist[it->v]) {
               dist[it->v] = dist[u] + it->peso;
               pred[it->v] = u;
            }
         }
      }
   }
   for (size_t u = 0; u < V; ++u) {
      for (auto it : adj[u]) {
         if (dist[u] != INF && dist[u] + it->peso < dist[it->v]) {
            return false;
         }
      }
   }
   custo = dist;
   caminhos = bellmanFordReconstruct(pred);
   return true;
}

std::vector<ii> Grafo::bellmanFordReconstruct(std::vector<int> pred) {
   std::set<ii> arestas;
   for (int i = 0; i < V; ++i) { //reconstroi o caminho para cada destino
      for (int atual = i; pred[atual] != -1; atual = pred[atual]) {
         arestas.insert({pred[atual], atual});
      }
   }
   return std::vector<ii>(arestas.begin(), arestas.end());
}

std::vector<ii> Grafo::kruskal(int &custo) {
   std::vector<Aresta *> arestas = toArestas();
   std::vector<ii> mst;
   std::sort(arestas.begin(), arestas.end(), Aresta::comp);

   int pred[V]; //union-find
   for (int i = 0; i < V; ++i) {
      pred[i] = i;
   }

   for (int i = custo = 0; i < arestas.size(); ++i) {
      Aresta *aresta = arestas[i];
      int pa = findset(pred, aresta->getU()->getId());
      int pb = findset(pred, aresta->getV()->getId());

      //se n estao no msm conjunto, adicionamos a aresta e n ira formar ciclo
      if (pa != pb) { 
         custo += aresta->getPeso();
         pred[pa] = pb;
         mst.push_back({aresta->getU()->getId(), aresta->getV()->getId()});
      }
   }
   for (size_t i = 0; i < arestas.size(); ++i) {
      delete arestas[i];
   }
   return mst;
}

std::vector<Aresta *> Grafo::toArestas() {
   std::vector<Aresta *> arestas;
   for (size_t i = 0; i < V; ++i) {
      for (auto it : adj[i]) {
         int v = it->v;
         int w = it->peso;
         if (i < v)  {
            arestas.push_back(new Aresta(w, new Vertice(i), new Vertice(v)));
         }
      }
   }
   return arestas;
}

int Grafo::findset(int v[], int x) {
   if (x != v[x])
      v[x] = findset(v, v[x]);
   return v[x];
}

std::vector<ii> Grafo::prim(int src, int &custo) {
   std::vector<ii> res;
   std::vector<int> key(V, INF);
   std::vector<ii> pred(V, {-1, 0});
   std::vector<bool> inMST(V, false); //vertices inclusos na MST
   std::priority_queue<ii, std::vector<ii>, std::greater<ii>> pq;

   pq.push({0, src}); //chave do vertice inicial sera 0
   key[src] = 0;

   while (!pq.empty()) {
      int u = pq.top().second; pq.pop();
      inMST[u] = true;
      for (auto it : adj[u]) {
         int v = it->v;
         int w = it->peso;
         if (!inMST[v] && key[v] > w) {
            key[v] = w;
            pred[v] = {u, w};
            pq.push({key[v], v});
         }
      }
   }
   for (int i = custo = 0; i < V; ++i) {
      if (i != src) {
         res.push_back({pred[i].first, i});
         custo += pred[i].second;
      }
   }
   return res;
}

int Grafo::fordFulkerson(int src, int dst, std::vector<int> adj[], LinkFF edges[]) {
   createResGraph(adj, edges);

   int flow = 0, tempo = 1;
   int seen[V] = {};
   while (int a = augPath(src, dst, INF, seen, tempo, adj, edges)) {
      flow += a;
      ++tempo;
   }
   return flow;
}

int Grafo::augPath(int s, int t, int f, int seen[], int tempo,
std::vector<int> adj[], LinkFF edges[]) {
   if (s == t) return f;
   seen[s] = tempo;
   for (int e : adj[s]) {
      if (seen[edges[e].to] < tempo && edges[e].c - edges[e].f > 0) {
         if (int a = augPath(edges[e].to, t, 
         std::min(f, edges[e].c - edges[e].f), seen, tempo, adj, edges)) {
            edges[e].f += a;
            edges[e ^ 1].f -= a;
            return a;
         }
      }
   }
   return 0;
}

void Grafo::createResGraph(std::vector<int> adj[], LinkFF edges[]) {
   int curr = 0;
   for (size_t u = 0; u < V; ++u) {
      for (auto it : this->adj[u]) {
         int v = it->v;
         if (u < v) {
            //add aresta e aresta reversa
            edges[curr].to = v; edges[curr].f = 0; edges[curr].c = it->peso;  
            edges[curr].reversa = false;
            adj[u].push_back(curr++);
            edges[curr].to = u; edges[curr].f = 0; edges[curr].c = 0;
            edges[curr].reversa = true;
            adj[v].push_back(curr++);
         } else if (u > v) { 
            //entao verifica se ja n existe as arestas
            //e apenas atualiza a aresta reversa
            std::vector<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
               if (edges[*i].to == v) {
                  edges[*i].c = it->peso;
                  edges[*i].reversa = false;
                  break;
               }
            }
            if (i == adj[u].end()) { //se n existia aresta reversa
               edges[curr].to = v; edges[curr].f = 0; edges[curr].c = it->peso;
               edges[curr].reversa = false;
               adj[u].push_back(curr++);
               edges[curr].to = u; edges[curr].f = 0; edges[curr].c = 0;
               edges[curr].reversa = true;
               adj[v].push_back(curr++);
            }
         }
      }
   }
}

void Grafo::sort() {
   for (size_t i = 0; i < V; ++i) {
      std::sort(adj[i].begin(), adj[i].end(), Link::comp);
   }
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
         delete vertices[i]; vertices[i] = nullptr;
      }
   }
   delete [] adj; adj = nullptr;
}
