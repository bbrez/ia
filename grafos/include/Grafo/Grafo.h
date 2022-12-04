#ifndef GRAFO_H
#define GRAFO_H

#include <Grafo/Vertice.h>
#include <Grafo/Aresta.h>
#include <Grafo/Cor.h>
#include <Grafo/Caminho.h>
#include <Grafo/Heuristica.h>

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <optional>

namespace Grafos {
class Grafo {
public:

    Grafo(bool isDirecionado);
    ~Grafo();

    void adicionarVertice(const std::string& nome);
    void adicionarAresta(const std::string& origem, const std::string& destino, int peso);

    void imprimirGrafo();

    std::optional<Caminho> buscaEmProfundidade(const std::string& origem, const std::string& destino);
    std::optional<Caminho> buscaEmLargura(const std::string& origem, const std::string& destino);

    std::optional<Caminho> dijkstra(const std::string& origem, const std::string& destino);

    std::optional<Caminho> a_star(const std::string& origem, const std::string& destino, Heuristica heuristica);

    void to_dot(const std::string& filename);

private:

    const bool isDirecionado;
    std::map<std::string, std::shared_ptr<Vertice>> vertices;
};
} // namespace Grafos

#endif