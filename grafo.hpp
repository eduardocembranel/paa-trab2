#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>

#include "vertice.hpp"
#include "aresta.hpp"

typedef std::pair<int, int> ii;

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

      void dfsVisit(int, bool*, std::vector<ii> &);

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

      std::vector<ii> dfs(int);
      std::vector<ii> bfs(int);
      std::vector<int> bFord(int);
      std::vector<ii> kruskal(int &);
      std::vector<ii> prim(int, int &);
};

#endif // !GRAFO_HPP