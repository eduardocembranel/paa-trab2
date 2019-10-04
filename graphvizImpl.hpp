#ifndef GRAPHVIZIMPL
#define GRAPHVIZIMPL

#include <graphviz/gvc.h>
#include <string>

#include "grafo.hpp"

bool saveImageGV(std::string);

void grapoToDot(Grafo *, std::string);

#endif // !GRAPHVIZIMPL
