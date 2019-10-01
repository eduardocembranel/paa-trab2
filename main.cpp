#include <iostream>
#include "grafo.hpp"

using namespace std;

int main() {
   Vertice *v0 = new Vertice(0);
   Vertice *v1 = new Vertice(1);
   Vertice *v2 = new Vertice(2);
   Vertice *v3 = new Vertice(3);
   Vertice *v4 = new Vertice(4);
   Vertice *v5 = new Vertice(5);
   Vertice *v6 = new Vertice(6);
   Vertice *v7 = new Vertice(7);
   Vertice *v8 = new Vertice(8);

   std::vector<Vertice *> vertices;
   vertices.push_back(v0);
   vertices.push_back(v1);
   vertices.push_back(v2);
   vertices.push_back(v3);
   vertices.push_back(v4);
   vertices.push_back(v5);
   vertices.push_back(v6);
   vertices.push_back(v7);
   vertices.push_back(v8);
   Grafo *g = new Grafo(9, vertices, true);

   g->addAresta(new Aresta(std::string(), 4, v0, v1));
   g->addAresta(new Aresta(std::string(), 8, v0, v7));
   g->addAresta(new Aresta(std::string(), 4, v1, v0));
   g->addAresta(new Aresta(std::string(), 11, v1, v7));
   g->addAresta(new Aresta(std::string(), 8, v1, v2));
   g->addAresta(new Aresta(std::string(), 8, v2, v1));
   g->addAresta(new Aresta(std::string(), 7, v2, v3));
   g->addAresta(new Aresta(std::string(), 4, v2, v5));
   g->addAresta(new Aresta(std::string(), 2, v2, v8));
   g->addAresta(new Aresta(std::string(), 7, v3, v2));
   g->addAresta(new Aresta(std::string(), 9, v3, v4));
   g->addAresta(new Aresta(std::string(), 14, v3, v5));
   g->addAresta(new Aresta(std::string(), 9, v4, v3));
   g->addAresta(new Aresta(std::string(), 10, v4, v5));
   g->addAresta(new Aresta(std::string(), 4, v5, v2));
   g->addAresta(new Aresta(std::string(), 14, v5, v3));
   g->addAresta(new Aresta(std::string(), 10, v5, v4));
   g->addAresta(new Aresta(std::string(), 2, v5, v6));
   g->addAresta(new Aresta(std::string(), 2, v6, v5));
   g->addAresta(new Aresta(std::string(), 1, v6, v7));
   g->addAresta(new Aresta(std::string(), 6, v6, v8));
   g->addAresta(new Aresta(std::string(), 8, v7, v0));
   g->addAresta(new Aresta(std::string(), 11, v7, v1));
   g->addAresta(new Aresta(std::string(), 1, v7, v6));
   g->addAresta(new Aresta(std::string(), 7, v7, v8));
   g->addAresta(new Aresta(std::string(), 2, v8, v2));
   g->addAresta(new Aresta(std::string(), 6, v8, v6));
   g->addAresta(new Aresta(std::string(), 7, v8, v7));

   g->sort();

   //std::vector<int> res = g->bFord(0);
   //for (auto it : res) {
   //   cout << it << endl;
   //}

   int peso = 0;
   std::vector<std::pair<int, int>> res = g->prim(0, peso);// g->kruskal(peso);
   std::cout << peso << std::endl;
   for (int i = 0; i < res.size(); ++i) {
      std::cout << res[i].first << " " << res[i].second << std::endl;
   }
   return 0;
}