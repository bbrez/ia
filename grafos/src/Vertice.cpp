#include <Grafo/Vertice.h>
#include <Grafo/Aresta.h>

namespace Grafos {
Vertice::Vertice(const std::string& nome) : nome(nome) {}

Vertice::Vertice(std::string& nome) : nome(nome) {}

Vertice::~Vertice() {}

auto Vertice::operator<=>(const Vertice& other) const {
    return nome <=> other.nome;
}

void Vertice::adicionarAresta(std::shared_ptr<Aresta> aresta) {
    if (arestas.find(aresta->getDestino()->getNome()) == arestas.end()) {
        arestas[aresta->getDestino()->getNome()] = aresta;
    }
}

std::string Vertice::getNome() const {
    return nome;
}

ListaArestas Vertice::getArestas() const {
    return arestas;
}

} // namespace Grafos