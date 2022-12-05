#ifndef CAMINHO_H
#define CAMINHO_H

#include <Grafo/Vertice.h>

#include <vector>
#include <memory>

namespace Grafos {
typedef std::vector<std::shared_ptr<Vertice>> caminho_t;

class Caminho : public std::vector<std::shared_ptr<Vertice>> {
private:

    int visitados = 0;

public:

    Caminho() = default;
    ~Caminho() = default;

    void incrementarVisitados();

    int getComprimento() const;
    int getDistancia() const;
    int getVisitados() const;

    void imprimir();
};

} // namespace Grafos

#endif