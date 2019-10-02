#include <iostream>

#include "vertice.hpp"

Vertice::Vertice() {
}

Vertice::Vertice(const std::string &label) {
   this->label = label;
}

Vertice::Vertice(int id) {
   this->id = id;
}

Vertice::Vertice(const std::string &label, int id) {
   this->label = label;
   this->id = id;
}

void Vertice::setLabel(std::string label) {
   this->label = label;
}

void Vertice::setId(int id) {
   this->id = id;
}

std::string Vertice::getLabel() const {
   return label;
}

int Vertice::getId() const {
   return id;
}

void Vertice::show() const {
   std::cout << "id=" << id << "\n";
}

Vertice::~Vertice() {

}
