#ifndef GRAPHDRAWER
#define GRAPHDRAWER

#include <string>
#include <fstream>

#include "grafo.hpp"

class GraphDrawer {
   public:
      GraphDrawer();
   //private:
      bool saveImageGV(std::string);
      
      void drawGraph(Grafo *, std::string);
      void drawGraphHighlighted(Grafo *, std::string, std::vector<ii>, int=-1);
      
      //n precisa passar a string
      void drawGraphBellmanFord(Grafo *, std::string, std::vector<ii>, int, 
      std::vector<int>);
      
      
      void drawGraphFordFulkerson(Grafo *, std::vector<int> [], LinkFF [], 
      int, int);

      void setGraphAttr(std::ofstream &, std::string);
      void setNodeAttr(std::ofstream &);
      void setEdgeAttr(std::ofstream &, bool);
      void nodeDefine(std::ofstream &, Grafo *, int=-1, int=-1);
      void nodeDefineBellmanFord(std::ofstream &, Grafo *, int, std::vector<int>);    void edgeDefine(std::ofstream &, Grafo *);
      void edgeDefineHighlighted(std::ofstream &, Grafo *, std::vector<ii>);
      void edgeDefineFordFulkerson(std::ofstream &, Grafo *, std::vector<int> [],
      LinkFF []);
};

#endif // !GRAPHDRAWER