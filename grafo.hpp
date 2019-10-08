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

      std::vector<ii> bellmanFordReconstruct(std::vector<int>);

      void createResGraph(std::vector<int> [], LinkFF []);

      int augPath(int, int, int, int *, int, std::vector<int> [], LinkFF []);

   public:
      Grafo();
      Grafo(int, std::vector<Vertice *>, bool=false);

      //copy constructor
      Grafo(Grafo &);


      ~Grafo();
      int getNumV() const;
      int getNumE() const;
      void addAresta(Aresta *);
      std::vector<Link *> * getAdj();
      std::vector<Vertice *> getVertices();
      std::string getLabelVertice(int);
      bool isOrientado() const;

      void sort();

      void show() const; //debug

      std::vector<ii> dfs(int); //ok
      std::vector<ii> bfs(int); //ok
      std::vector<ii> kruskal(int &); //ok
      std::vector<ii> prim(int, int &); //ok
      bool bellmanFord(int, std::vector<ii> &, std::vector<int> &); //ok
      int fordFulkerson(int, int, Grafo *&);
};

#endif // !GRAFO_HPP
