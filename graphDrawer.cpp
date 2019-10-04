#include <graphviz/gvc.h>
#include <cstdlib>
#include <set>

#include "graphDrawer.hpp"

GraphDrawer::GraphDrawer() {

}

bool GraphDrawer::saveImageGV(std::string file_path){
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

void GraphDrawer::grapoToDot(Grafo *grafo, std::string algoritmo, int vDestaque) {
   std::ofstream file (algoritmo + ".dot");
   if (grafo->isOrientado())
      file << "digraph grafo {" << std::endl;
   else 
      file << "graph grafo {" << std::endl;

   setGraphAttr(file, algoritmo);
   setNodeAttr(file);
   setEdgeAttr(file, grafo->isOrientado());
   nodeDefine(file, grafo, vDestaque);
   edgeDefine(file, grafo);

   file << "}";
   file.close();
}

void GraphDrawer::setGraphAttr(std::ofstream &file, std::string titulo) {
   file << "  graph ["                      << std::endl
        << "    charset = \"UTF-8\";"       << std::endl
        << "    bgcolor = gray100,"         << std::endl
        << "    label =\" " + titulo + "\""  << std::endl
        << "    labelloc = \"t\","          << std::endl
        << "    labeljust = \"c\","         << std::endl
        << "    fontcolor = black,"         << std::endl
        << "    fontname= \"helvetica\","   << std::endl
        << "    fontsize = 40,"             << std::endl
        << "    style = \"filled\","        << std::endl
        << "    rankdir = LR,"              << std::endl
        << "    splines = spline,"          << std::endl
        << "    ranksep = 3.0,"             << std::endl
        << "    nodesep = 4.5"              << std::endl
        << "    overlap = false"            << std::endl
        << "  ];"                           << std::endl << std::endl;
}

void GraphDrawer::setNodeAttr(std::ofstream &file) {
   file << "  node ["                      << std::endl
        << "    style = \"solid,filled\"," << std::endl
        << "    color = violet,"           << std::endl
        << "    fontsize = 35,"            << std::endl
        << "    fontcolor = black,"        << std::endl
        << "    fontname = helvetica,"     << std::endl
        << "    height = 0.6,"             << std::endl
        << "    width = 1.2"               << std::endl
        << "  ];"                          << std::endl << std::endl;
}

void GraphDrawer::setEdgeAttr(std::ofstream &file, bool orientado) {
   file << "  edge ["                  << std::endl
        << "    style = solid,"        << std::endl
        << "    fontsize = 30,"        << std::endl
        << "    fontname = helvetica," << std::endl
        << "    color = black,"        << std::endl
        << "    arrowhead = normal,"   << std::endl
        << "    penwidth= 2.0\n"       << std::endl
        << "  ];"                      << std::endl << std::endl;
}

void GraphDrawer::nodeDefine(std::ofstream &file, Grafo *grafo, int vDestaque) {
   file << "  //node define" << std::endl;
   for (size_t i = 0; i < grafo->getNumV(); ++i) {
      auto it = grafo->getVertices()[i];
      if (it->getLabel() == "") {
         file << "  " << it->getId() << " [shape = circle";
      } else {
         file << "  \"" << it->getLabel() << "\" [shape = rectangle";
      }
      if (i == vDestaque) {
         file << ", color=yellow];\n";
      } else {
         file << "];\n";
      }
   }
   file << std::endl;
}

void GraphDrawer::edgeDefine(std::ofstream &file, Grafo *grafo) {
   file << "  //edge define" << std::endl;
   std::string edge = (grafo->isOrientado()) ? " -> " : " -- ";
   std::string lblU, lblV;

   for (size_t u = 0; u < grafo->getNumV(); ++u) {
      //Vertice u:
      Vertice *vert = grafo->getVertices()[u];
      if (vert->getLabel() == "")
         lblU = std::to_string(vert->getId());
      else
         lblU = "\"" + vert->getLabel() + "\"";

      //Vertice v:s
      for (auto it : grafo->getAdj()[u]) {
         int v = it->v;
         if (grafo->isOrientado() || u <= v) {
            Vertice *vert = grafo->getVertices()[v];
            if (vert->getLabel() == "")
               lblV = std::to_string(vert->getId());
            else
               lblV = "\"" + vert->getLabel() + "\"";

            file << "  " << lblU << edge << lblV << " ";

            //custom edge
            file << "[";
            if (it->label != "") {
               file << "label = <<font color=\"blue\">" + it->label + "</font>>, ";
            }
            file << "xlabel = <<font color=\"black\">" 
               + std::to_string(it->peso) + "</font>>, ";
            file << "arrowhead = normal];\n";
         }
      }
   }
}