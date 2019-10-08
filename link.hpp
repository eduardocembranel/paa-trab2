#ifndef LINK_HPP
#define LINK_HPP

#include <string>

#define MAXE 100010

struct Link {
   std::string label; //label conexao
   int peso, v; //peso da conexao e id do vertice destino

   Link(std::string, int, int);

   static bool comp(Link *, Link *);
};

struct LinkFF {
   int to, f, c;
   bool reversa;
};

#endif // !LINK_HPP
