#ifndef APP_HPP
#define APP_HPP

#include "grafo.hpp"

class App {
   public:
      App();
      void loop();
      ~App();

   private:
      enum opcoesMenu {INDEFINIDO = -1, DFS = 1, BFS, BF, KRUSKAL, PRIM, 
      FFURKERSON, CARREGAR, DESENHAR, SAIR};

      Grafo *grafo;

      void limpaTela();

      void limpaBuffer();

      void pressionaParaRetornar();

      void mostraMenu();

      void driverCarregar();

      bool carregaGrafo(std::string);

      int askVertice();
      void runDFS(int);
      void runBFS(int);
      void runPrim(int);
      void runFFurkerson(int);
      void runBFord(int);
      void runKruskal();
};

#endif // !APP_HPP
