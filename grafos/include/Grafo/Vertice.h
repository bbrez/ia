#ifndef VERTICE_H
#define VERTICE_H

#include <map>
#include <string>
#include <memory>

namespace Grafos {
class Aresta;

typedef std::map<std::string, std::shared_ptr<Aresta>> ListaArestas;

class Vertice {
public:

    Vertice(const std::string& nome);
    Vertice(std::string& nome);
    ~Vertice();

    auto operator<=>(const Vertice&) const;

    void adicionarAresta(std::shared_ptr<Aresta> aresta);

    std::string getNome() const;
    ListaArestas getArestas() const;

private:

    std::string nome;
    ListaArestas arestas;
};
} // namespace Grafos
#endif