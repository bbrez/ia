#include <Grafo/Aresta.h>

namespace Grafos {
Aresta::Aresta(int peso) : peso(peso) {}

Aresta::~Aresta() {}

auto Aresta::operator<=>(const Aresta& other) const {
    return peso <=> other.peso;
}

void Aresta::setOrigem(std::shared_ptr<Vertice> origem) {
    this->origem = origem;
}

void Aresta::setDestino(std::shared_ptr<Vertice> destino) {
    this->destino = destino;
}

std::shared_ptr<Vertice> Aresta::getOrigem() const {
    return origem;
} // namespace Grafos

std::shared_ptr<Vertice> Aresta::getDestino() const {
    return destino;
}

int Aresta::getPeso() const {
    return peso;
}
} // namespace Grafos