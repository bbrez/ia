#include <Grafo/Caminho.h>
#include <Grafo/Aresta.h>

#include <iostream>

namespace Grafos {

void Caminho::imprimir() {
    std::string saida = "";
    for (auto& vertice : *this) {
        if (!saida.empty()) saida += " -> ";
        saida += vertice->getNome();
    }

    std::cout << saida << std::endl;
}

int Caminho::getDistancia() const {
    int distancia = 0;

    for (auto i = 0llu; i < size() - 1; i++) {
        distancia += at(i)->getArestas()[at(i + 1)->getNome()]->getPeso();
    }

    return distancia;
}

int Caminho::getComprimento() const {
    return this->size();
}

int Caminho::getVisitados() const {
    return visitados;
}

void Caminho::incrementarVisitados() {
    visitados++;
}


} // namespace Grafos