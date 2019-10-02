#include <iostream>
#include "grafo.hpp"

using namespace std;

int main() {
   Vertice *va = new Vertice(0);
   Vertice *vb = new Vertice(1);
   Vertice *vc = new Vertice(2);
   Vertice *vd = new Vertice(3);
   Vertice *ve = new Vertice(4);

   std::vector<Vertice *> vertices;
   vertices.push_back(va);
   vertices.push_back(vb);
   vertices.push_back(vc);
   vertices.push_back(vd);
   vertices.push_back(ve);
   Grafo *g = new Grafo(5, vertices, true);

   g->addAresta(new Aresta(std::string(), -1, va, vb));
   g->addAresta(new Aresta(std::string(), 4, va, vc));
   g->addAresta(new Aresta(std::string(), 3, vb, vc));
   g->addAresta(new Aresta(std::string(), 2, vb, ve));
   g->addAresta(new Aresta(std::string(), 2, vb, vd));
   g->addAresta(new Aresta(std::string(), 5, vd, vc));
   g->addAresta(new Aresta(std::string(), 1, vd, vb));
   g->addAresta(new Aresta(std::string(), -3, ve, vd));
   g->sort();

   std::vector<std::pair<int, int>> path;
   std::vector<int> dist;

   if (g->bFord(0, path, dist)) {
      for (auto it : dist) {
         std::cout << it << std::endl;
      }
      std::cout << "\n";
      for (auto it : path) {
         std::cout << it.first << " -> " << it.second << "\n";
      }
   } else {
      std::cout << "ciclo negativo\n";
   }

   //std::vector<int> res = g->bFord(0);
   //for (auto it : res) {
   //   cout << it << endl;
   //}

   return 0;
}
