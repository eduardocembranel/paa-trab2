#include <iostream>
#include <limits>
#include <fstream>
#include <regex>

#include "app.hpp"
#include "grafo.hpp"
#include "util.hpp"
#include "graphDrawer.hpp"

App::App() {
   grafo = nullptr;
}

void App::loop() {
   int escolha = INDEFINIDO;
   while (escolha != SAIR) {
      mostraMenu();
      std::cin >> escolha;
      limpaBuffer();
      if (escolha >= DFS && escolha <= FORDFURKERSON && grafo == nullptr) {
         std::cerr << "\nGrafo nao carregado!\n";
         pressionaParaRetornar();
      } else if (escolha == DFS) {
         int vertice = askVertice();
         runDFS(vertice);
      } else if (escolha == BFS) {
         int vertice = askVertice();
         runBFS(vertice);
      } else if (escolha == BELLMANFORD) {
         int vertice = askVertice();
         runBellmanFord(vertice);
      } else if (escolha == KRUSKAL) {
         runKruskal();
      } else if (escolha == PRIM) {
         int vertice = askVertice();
         runPrim(vertice);
      } else if (escolha == FORDFURKERSON) {
         int s, t;
         askSourceDst(s, t);
         runFordFurkerson(s, t);
      } else if (escolha == CARREGAR) {
         driverCarregar();
      } else if (escolha == DESENHAR) {
         GraphDrawer *g = new GraphDrawer();
         g->grapoToDot(grafo, "BFS");
      } else if (escolha != SAIR) {
         std::cerr << "\nOpcao invalida!\n";
         pressionaParaRetornar();
      }
   }
}

void App::driverCarregar() {
   limpaTela();
   std::cout << "[CARREGAR GRAFO]\n\n";
   std::cout << "Insira o caminho do arquivo de entrada: ";
   std::string caminhoArquivo;
   std::cin >> caminhoArquivo;
   limpaBuffer();
   if (carregaGrafo(caminhoArquivo)) {
      std::cout << "\nGrafo carregado com sucesso!\n\n";
   } else {
      std::cerr << "\nArquivo nao encontrado!\n\n";
   }
   pressionaParaRetornar();
}

int App::askVertice() {
   int vertice;
   std::cout << ">> Vertice Inicial: ";
   std::cin >> vertice;
   limpaBuffer();
   return vertice;
}

void App::askSourceDst(int &s, int &t) {
   std::cout << ">> Vertice fonte: ";
   std::cin >> s;
   std::cout << ">> Vertice ralo: ";
   std::cin >> t;
   limpaBuffer();
}

void App::runDFS(int src) {
   limpaTela();
   std::cout << "[DFS]\n\n";

   std::vector<ii> res = grafo->dfs(src);
   for (auto it : res) {
      std::cout << it.first << "," << it.second << "\n";
   }
   //salva arquivo

   std::cout << "Arvore resultante em dfs.png\n";
   pressionaParaRetornar();
}

void App::runBFS(int src) {
   limpaTela();
   std::cout << "[BFS]\n\n";

   std::vector<ii> res = grafo->bfs(src);
   for (auto it : res) {
      std::cout << it.first << "," << it.second << "\n";
   }
   //salva arquivo

   std::cout << "Arvore resultante em bfs.png\n";
   pressionaParaRetornar();
}

void App::runBellmanFord(int src) {
   limpaTela();
   std::cout << "[BELLMAN-FORD]\n\n";

   std::vector<ii> caminhos;
   std::vector<int> custos;
   if (grafo->bellmanFord(src, caminhos, custos)) {
      for (auto it : caminhos) {
         std::cout << it.first << "," << it.second << "\n";
      }
      std::cout << "\nCustos:\n";
      for (auto it : custos) {
         std::cout << it << "\n";
      }
      //desenha
   } else {
      std::cerr << "\nCiclo de peso negativo encontrado\n";
   }
   pressionaParaRetornar();
}

void App::runKruskal() {
   limpaTela();
   std::cout << "[KRUSKAL]\n\n";

   int custo;
   std::vector<ii> res = grafo->kruskal(custo);
   //salva arquivo

   std::cout << "Custo: " << custo << "\n";
   std::cout << "MST resultante em kruskal.png\n\n";
   pressionaParaRetornar();
}

void App::runPrim(int src) {
   limpaTela();
   std::cout << "[PRIM]\n\n";

   int custo;
   std::vector<ii> res = grafo->prim(src, custo);
   //salva arquivo

   std::cout << "Custo: " << custo << "\n";
   std::cout << "MST resultante em prim.png\n\n";
   pressionaParaRetornar();
}

void App::runFordFurkerson(int src, int dst) {
   limpaTela();
   std::cout << "[FORD-FURKERSON]\n\n";

   Grafo *novo = nullptr;
   int fluxoMaximo = grafo->fordFurkerson(src, dst, novo);
   std::cout << "Fluxo Maximo: " << fluxoMaximo << "\n";

   //salva

   pressionaParaRetornar();
}

void App::pressionaParaRetornar() {
   std::cout << "Pressione ENTER para retornar...";
   limpaBuffer();
}

void App::limpaTela() {
   system("clear");
}

void App::limpaBuffer() {
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void App::mostraMenu() {
   limpaTela();
   std::cout << "[MENU PRINCIPAL]\n\n"
             << "[1]DFS\n"
             << "[2]BFS\n"
             << "[3]Bellman-Ford\n"
             << "[4]Kruskal\n"
             << "[5]Prim\n"
             << "[6]Ford-Fulkerson\n"
             << "[7]Carregar Grafo\n"
             << "[8]Desenhar Grafo\n"
             << "[9]Sair\n"
             << ">> ";
}

bool App::carregaGrafo(std::string caminho) {
   std::ifstream arquivo(caminho);
   if (arquivo.fail()) {
      return false;
   }
   std::string line;
   std::vector<Vertice *> vertices; //vetor dos vertices
   int V; //numero de vertices

   //1a linha
   std::getline(arquivo, line);
   bool orientado = (line.find("sim") != std::string::npos);
   
   //2a linha
   std::getline(arquivo, line);
   if (line.find('{') != std::string::npos) {
      line = line.substr(line.find("{") + 1);
      std::vector<std::string> labels = split(line, ",}");
      V = labels.size();
      for (int i = 0; i < V; ++i) {
         vertices.push_back(new Vertice(labels[i], i));
      }
   } else {
      V = strToInt(line.substr(line.find("=") + 1));
      for (int i = 0; i < V; ++i) {
         vertices.push_back(new Vertice(i));
      }
   }

   //inicializa grafo
   if (grafo != nullptr) {
      delete grafo; grafo = nullptr;
   }
   grafo = new Grafo(V, vertices, orientado);

   //3a linha em diante
   while (std::getline(arquivo, line)) {
      if (isOnlySpaces(line)) {
         continue;
      }

      int u, v, w;
      std::string label;

      //obtem aresta (u, v) e peso
      line = line.substr(line.find('(') + 1);
      std::stringstream ss(line);
      ss >> u;
      line = line.substr(line.find(',') + 1);
      ss.str(line);
      ss >> v;
      line = line.substr(line.find(':') + 1);
      ss.str(line);
      ss >> w;

      //obtem label, se existir
      size_t foundPos = line.find(',');
      if (foundPos == std::string::npos) {
         label = "";
      } else {
         line = line.substr(foundPos + 1);
         ss.str(line);
         std::getline(ss, label);
      }

      //insere no grafo
      Aresta *aresta = new Aresta(label, w, new Vertice(u), new Vertice(v));
      grafo->addAresta(aresta);
      delete aresta; aresta = nullptr;
   }
   grafo->sort();
   return true;
}

App::~App() {
   delete grafo;
}
