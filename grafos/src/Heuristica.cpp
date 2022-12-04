#include <Grafo/Heuristica.h>

namespace Grafo {
Heuristica::Heuristica() = default;
Heuristica::~Heuristica() = default;

void Heuristica::adicionarHeuristica(const std::string& origem, const std::string& destino, int peso) {
    heuristica[origem][destino] = peso;
}

int Heuristica::getHeuristica(const std::string& origem, const std::string& destino) {
    return heuristica[origem][destino];
}
} // namespace Grafo
