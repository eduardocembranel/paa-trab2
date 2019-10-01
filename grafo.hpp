#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>

#include "vertice.hpp"
#include "aresta.hpp"

struct Link {
   std::string label; //label conexao
   int peso; //peso da conexao
   int v; //id do vertice destino

   Link(std::string label, int peso, int v) {
      this->label = label;
      this->peso = peso;
      this->v = v;
   }
};

class Grafo {
   private:
      int V; //num vertices

      int E; //num arestas

      std::vector<Link *> *adj; //lista de adjacencia

      std::vector<Vertice *> vertices; //lista de vertices

      bool orientado;

      void dfsVisit(int, bool*, std::vector<std::pair<int, int>> &);

      static bool comp(Link *, Link *);

      std::vector<Aresta *> toArestas();

      int findset(int *, int);

   public:
      Grafo();
      Grafo(int, std::vector<Vertice *>, bool=false);
      ~Grafo();
      int getNumV() const;
      void addAresta(Aresta *);

      void sort();
      void show() const;

      std::vector<std::pair<int, int>> dfs(int);
      std::vector<std::pair<int, int>> bfs(int);
      std::vector<int> bFord(int);
      std::vector<std::pair<int, int>> kruskal(int &);
};

#endif // !GRAFO_HPP