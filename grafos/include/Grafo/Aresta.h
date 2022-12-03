#ifndef ARESTA_H
#define ARESTA_H

#include <memory>

namespace Grafos {
class Vertice;

class Aresta {
public:

    Aresta(int peso);
    ~Aresta();

    auto operator<=>(const Aresta&) const;

    void setOrigem(std::shared_ptr<Vertice> origem);
    void setDestino(std::shared_ptr<Vertice> destino);

    std::shared_ptr<Vertice> getOrigem() const;
    std::shared_ptr<Vertice> getDestino() const;

    int getPeso() const;

private:

    std::shared_ptr<Vertice> origem;
    std::shared_ptr<Vertice> destino;
    const int peso;
};
} // namespace Grafos
#endif