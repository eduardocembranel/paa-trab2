#ifndef APP_HPP
#define APP_HPP

#include "grafo.hpp"
#include "graphDrawer.hpp"

class App {
   public:
      App();
      void loop();
      ~App();

   private:
      enum opcoesMenu {INDEFINIDO = -1, DFS = 1, BFS, BELLMANFORD, KRUSKAL, PRIM, 
      FORDFULKERSON, CARREGAR, DESENHAR, SAIR};

      Grafo *grafo;
      GraphDrawer *drawer;

      void limpaTela();

      void limpaBuffer();

      void pressionaParaRetornar();

      void mostraMenu();

      void driverCarregar();

      void driverDesenhar();

      bool carregaGrafo(std::string);

      int askVertice();

      void askSourceDst(int &, int &);

      void runDFS(int);
      void runBFS(int);
      void runPrim(int);
      void runFordFulkerson(int, int);
      void runBellmanFord(int);
      void runKruskal();
};

#endif // !APP_HPP
