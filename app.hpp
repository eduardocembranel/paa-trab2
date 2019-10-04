#ifndef APP_HPP
#define APP_HPP

#include "grafo.hpp"

class App {
   public:
      App();
      void loop();
      ~App();

   private:
      enum opcoesMenu {INDEFINIDO = -1, DFS = 1, BFS, BELLMANFORD, KRUSKAL, PRIM, 
      FORDFURKERSON, CARREGAR, DESENHAR, SAIR};

      Grafo *grafo;

      void limpaTela();

      void limpaBuffer();

      void pressionaParaRetornar();

      void mostraMenu();

      void driverCarregar();

      bool carregaGrafo(std::string);

      int askVertice();

      void askSourceDst(int &, int &);

      void runDFS(int);
      void runBFS(int);
      void runPrim(int);
      void runFordFurkerson(int, int);
      void runBellmanFord(int);
      void runKruskal();
};

#endif // !APP_HPP
