#ifndef LINK_HPP
#define LINK_HPP

#include <string>

struct Link {
   std::string label; //label conexao
   int peso; //peso da conexao
   int v; //id do vertice destino

   Link(std::string, int, int);

   static bool comp(Link *, Link *);
};

#endif // !LINK_HPP
