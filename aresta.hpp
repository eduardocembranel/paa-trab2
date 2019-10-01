#ifndef ARESTA_HPP
#define ARESTA_HPP

#include <string>

#include "vertice.hpp"

class Aresta {
   private:
      std::string label;
      Vertice *u;
      Vertice *v;
      int peso;

   public:
      Aresta();
      Aresta(const std::string &, int, Vertice *, Vertice *);
      Aresta(int, Vertice *, Vertice *);

      int getPeso() const;
      Vertice *getU() const;
      Vertice *getV() const;
      std::string getLabel() const;

      void setPeso(int);
      void setU(Vertice *);
      void setV(Vertice *);
      void setLabel(std::string); 

      static bool comp(Aresta *, Aresta *);

};

#endif // !ARESTA_HPP