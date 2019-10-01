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
   //Vertice *v6 = new Vertice(6);
   //Vertice *v7 = new Vertice(7);

   std::vector<Vertice *> vertices;
   vertices.push_back(v0);
   vertices.push_back(v1);
   vertices.push_back(v2);
   vertices.push_back(v3);
   vertices.push_back(v4);
   vertices.push_back(v5);
   //vertices.push_back(v6);
   //vertices.push_back(v7);
   Grafo *g = new Grafo(6, vertices, true);

   g->addAresta(new Aresta(std::string(), 1, v0, v1));
   g->addAresta(new Aresta(std::string(), 10, v1, v2));
   g->addAresta(new Aresta(std::string(), -50, v2, v3));
   g->addAresta(new Aresta(std::string(), 10, v3, v4));
   g->addAresta(new Aresta(std::string(), 2, v4, v2));

   g->sort();

   //g->show();
   //std::vector<std::pair<int, int>> res = g->bFord(0);
   //for (auto it : res) {
   //   std::cout << it.first << "," << it.second << std::endl;
   //}

   std::vector<int> res = g->bFord(0);

   for (auto it : res) {
      cout << it << endl;
   }

   return 0;
}