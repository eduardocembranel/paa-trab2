#include <graphviz/gvc.h>
#include <cstdlib>

#include "graphvizImpl.hpp"

bool saveImageGV(std::string file_path){
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen((file_path).c_str(), "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fopen((file_path + ".png").c_str(), "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    return (gvFreeContext(gvc));
}

void grapoToDot(Grafo *grafo, std::string arquivo) {
   
}
