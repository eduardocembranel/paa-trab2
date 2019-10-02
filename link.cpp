#include "link.hpp"

Link::Link(std::string label, int peso, int v) {
   this->label = label;
   this->peso = peso;
   this->v = v;
}

bool Link::comp(Link *a, Link *b) {
   return (a->v < b->v);
}
