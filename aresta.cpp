#include "aresta.hpp"

Aresta::Aresta() {

}

Aresta::Aresta(const std::string &label, int peso, Vertice *u, Vertice *v) {
   this->label = label;
   this->peso = peso;
   this->u = u;
   this->v = v;
}

Aresta::Aresta(int peso, Vertice *u, Vertice *v) {
   this->label = "";
   this->peso = peso;
   this->u = u;
   this->v = v;
}

int Aresta::getPeso() const {
   return peso;
}

Vertice *Aresta::getU() const {
   return u;
}

Vertice *Aresta::getV() const {
   return v;
}

std::string Aresta::getLabel() const {
   return label;
}

void Aresta::setPeso(int peso) {
   this->peso = peso;
}

void Aresta::setU(Vertice *u) {
   this->u = u;
}

void Aresta::setV(Vertice *v) {
   this->v = v;
}

void Aresta::setLabel(std::string label) {
   this->label = label;
}

bool Aresta::comp(Aresta *a, Aresta *b) {
   return (a->peso < b->peso);
}
