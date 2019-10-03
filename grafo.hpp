#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>

#include "vertice.hpp"
#include "aresta.hpp"
#include "link.hpp"

typedef std::pair<int, int> ii;

class Grafo {
   private:
      int V; //num vertices
      int E; //num arestas
      std::vector<Link *> *adj; //lista de adjacencia
      std::vector<Vertice *> vertices; //lista de vertices
      bool orientado;


      void dfsVisit(int, bool*, std::vector<ii> &);      

      std::vector<Aresta *> toArestas();

      int findset(int *, int);

      std::vector<ii> bFordReconstruct(std::vector<int>);

   public:
      Grafo();
      Grafo(int, std::vector<Vertice *>, bool=false);
      ~Grafo();
      int getNumV() const;
      void addAresta(Aresta *);
      void sort();

      void show() const; //debug

      std::vector<ii> dfs(int); //ok
      std::vector<ii> bfs(int); //ok
      std::vector<ii> kruskal(int &); //ok
      std::vector<ii> prim(int, int &); //ok
      bool bFord(int, std::vector<ii> &, std::vector<int> &); //ok
};

#endif // !GRAFO_HPP
