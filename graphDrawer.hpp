#ifndef GRAPHDRAWER
#define GRAPHDRAWER

#include <string>
#include <fstream>

#include "grafo.hpp"

class GraphDrawer {
   public:
      GraphDrawer();
   //private:
      std::string graphAttr;

      bool saveImageGV(std::string);
      
      void grapoToDot(Grafo *, std::string, int=-1);

      
      void setGraphAttr(std::ofstream &, std::string);
      void setNodeAttr(std::ofstream &);
      void setEdgeAttr(std::ofstream &, bool);
      void nodeDefine(std::ofstream &, Grafo *, int=-1);
      void edgeDefine(std::ofstream &, Grafo *);
};

#endif // !GRAPHDRAWER