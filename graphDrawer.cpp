#include <graphviz/gvc.h>
#include <cstdlib>
#include <set>

#include "graphDrawer.hpp"

#define INF 0x3f3f3f3f

GraphDrawer::GraphDrawer() {

}

bool GraphDrawer::saveImageGV(std::string file_path){
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen((file_path + ".dot").c_str(), "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fopen((file_path + ".png").c_str(), "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    return (gvFreeContext(gvc));
}

void GraphDrawer::drawGraph(Grafo *grafo, std::string algoritmo) {
   std::ofstream file (algoritmo + ".dot");
   if (grafo->isOrientado())
      file << "digraph grafo {" << std::endl;
   else 
      file << "graph grafo {" << std::endl;

   setGraphAttr(file, algoritmo);
   setNodeAttr(file);
   setEdgeAttr(file, grafo->isOrientado());
   nodeDefine(file, grafo);
   edgeDefine(file, grafo);

   file << "}";
   file.close();
   saveImageGV(algoritmo);
}

void GraphDrawer::drawGraphHighlighted(Grafo * grafo, std::string algoritmo, 
std::vector<ii> edges, int src) {
   std::ofstream file (algoritmo + ".dot");
   if (grafo->isOrientado())
      file << "digraph grafo {" << std::endl;
   else 
      file << "graph grafo {" << std::endl;

   setGraphAttr(file, algoritmo);
   setNodeAttr(file);
   setEdgeAttr(file, grafo->isOrientado());
   nodeDefine(file, grafo, src);
   edgeDefineHighlighted(file, grafo, edges);

   file << "}";
   file.close();
   saveImageGV(algoritmo);
}

void GraphDrawer::drawGraphBellmanFord(Grafo *grafo, std::string algoritmo, 
std::vector<ii> edges, int src, std::vector<int> dist) {
   std::ofstream file (algoritmo + ".dot");
   if (grafo->isOrientado())
      file << "digraph grafo {" << std::endl;
   else 
      file << "graph grafo {" << std::endl;

   setGraphAttr(file, algoritmo);
   setNodeAttr(file);
   setEdgeAttr(file, grafo->isOrientado());
   nodeDefineBellmanFord(file, grafo, src, dist);
   edgeDefineHighlighted(file, grafo, edges);

   file << "}";
   file.close();
   saveImageGV(algoritmo);
}

void GraphDrawer::drawGraphFordFulkerson(Grafo *grafo, Grafo *resGrafo, 
int src, int dst) {
   std::ofstream file ("FordFulkerson.dot");
   file << "digraph grafo {" << std::endl;

   setGraphAttr(file, "FordFulkerson");
   setNodeAttr(file);
   setEdgeAttr(file, grafo->isOrientado());
   nodeDefine(file, grafo, src, dst);
   edgeDefineFordFulkerson(file, grafo, resGrafo);

   file << "}";
   file.close();
   saveImageGV("FordFulkerson");
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
        << "    color = paleturquoise2,"   << std::endl
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
        << "    color = chartreuse1,"  << std::endl
        << "    arrowhead = normal,"   << std::endl
        << "    penwidth = 4.5,"       << std::endl
        << "    arrowsize = 1.5"       << std::endl
        << "  ];"                      << std::endl << std::endl;

}

void GraphDrawer::nodeDefine(std::ofstream &file, Grafo *grafo, int vDestaque,
int vDestaque2) {
   file << "  //node define" << std::endl;
   for (size_t i = 0; i < grafo->getNumV(); ++i) {
      auto it = grafo->getVertices()[i];
      if (it->getLabel() == "") {
         file << "  " << it->getId() << " [shape = circle";
      } else {
         file << "  \"" << it->getLabel() << "\" [shape = rectangle";
      }
      if (i == vDestaque || i == vDestaque2) {
         file << ", color=purple];\n";
      } else {
         file << "];\n";
      }
   }
   file << std::endl;
}

void GraphDrawer::nodeDefineBellmanFord(std::ofstream &file, Grafo *grafo, 
int vDestaque, std::vector<int> dist) {
   file << "  //node define" << std::endl;
   for (size_t i = 0; i < grafo->getNumV(); ++i) {
      auto it = grafo->getVertices()[i];
      if (it->getLabel() == "") {
         file << "  " << it->getId() << " [shape = circle, ";
      } else {
         file << "  \"" << it->getLabel() << "\" [shape = rectangle, ";
      }
      
      file << "xlabel = <<font color=\"red\">";
      if (dist[i] == INF) {
         file << "INF" << "</font>>";
      } else {
         file << std::to_string(dist[i]) << "</font>>";
      }
      
      if (i == vDestaque) {
         file << ", color=purple];\n";
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
      lblU = "\"" + grafo->getLabelVertice(u) + "\"";

      //Vertice v:s
      for (auto it : grafo->getAdj()[u]) {
         int v = it->v;
         if (grafo->isOrientado() || u <= v) {
            lblV = "\"" + grafo->getLabelVertice(v) + "\"";

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

void GraphDrawer::edgeDefineHighlighted(std::ofstream &file, Grafo *grafo,
std::vector<ii> edges) {
   file << "  //edge define" << std::endl;
   std::string edge = (grafo->isOrientado()) ? " -> " : " -- ";
   std::string lblU, lblV;
   std::set<ii> sii(edges.begin(), edges.end());

   //desenha as arestas destacadas
   for (auto it : sii) {
      int u = it.first;
      int v = it.second;
      lblU = "\"" + grafo->getLabelVertice(u) + "\"";
      lblV = "\"" + grafo->getLabelVertice(v) + "\"";

      file << "  " << lblU << edge << lblV << " ";

      //custom
      for (auto it2 : grafo->getAdj()[u]) {
         if (it2->v == v) {
            file << "[";
            if (it2->label != "") {
               file << "label = <<font color=\"blue\">" + it2->label + "</font>>, ";
            }
            file << "xlabel = <<font color=\"black\">" 
               + std::to_string(it2->peso) + "</font>>, ";
            file << "penwidth = 9.0, color = magenta, arrowhead = normal];\n";
            break;
         }
      }
   }

   for (size_t u = 0; u < grafo->getNumV(); ++u) {
      //Vertice u:
      lblU = "\"" + grafo->getLabelVertice(u) + "\"";

      //Vertice v:
      for (auto it : grafo->getAdj()[u]) {
         int v = it->v;

         //ignora as arestas q foram destacadas
         if (sii.find({u, v}) != sii.end()) {
            continue;
         } else if (!grafo->isOrientado() && sii.find({v, u}) != sii.end()) {
            continue;
         }

         //garante q arestas de grafos nao orientados n se dupliquem
         if (grafo->isOrientado() || u <= v) {
            lblV = "\"" + grafo->getLabelVertice(v) + "\"";

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

void GraphDrawer::edgeDefineFordFulkerson(std::ofstream &file, Grafo *grafo,
Grafo *resGrafo) {
   file << "  //edge define" << std::endl;
   std::string edge = (grafo->isOrientado()) ? " -> " : " -- ";
   std::string lblU, lblV;

   for (size_t u = 0; u < grafo->getNumV(); ++u) {
      //Vertice u:
      lblU = "\"" + grafo->getLabelVertice(u) + "\"";

      //Vertice v:
      for (size_t j = 0; j < grafo->getAdj()[u].size(); ++j) {
         Link *it  = grafo->getAdj()[u][j];
         Link *it2 = resGrafo->getAdj()[u][j];
         int v = it->v;

         if (grafo->isOrientado() || u <= v) {
            lblV = "\"" + grafo->getLabelVertice(v) + "\"";

            file << "  " << lblU << edge << lblV << " ";

            //custom edge
            file << "[";
            if (it->label != "") {
               file << "label = <<font color=\"blue\">" + it->label + "</font>>, ";
            }
            
            int flow = it->peso - it2->peso;
            std::string lblPeso = 
              std::to_string(flow) + "/" + std::to_string(it->peso);
            
            file << "xlabel = <<font color=\"black\">" 
               + lblPeso + "</font>>, ";
            file << "arrowhead = normal];\n";
         }
      }
   }
}
