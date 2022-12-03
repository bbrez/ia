#ifndef GRAFO_H
#define GRAFO_H

#include <Grafo/Vertice.h>
#include <Grafo/Aresta.h>
#include <Grafo/Cor.h>

#include <map>
#include <string>
#include <memory>

namespace Grafos {
class Grafo {
public:

    Grafo(bool isDirecionado);
    ~Grafo();

    void adicionarVertice(const std::string& nome);
    void adicionarAresta(const std::string& origem, const std::string& destino, int peso);

    void imprimirGrafo();

    void buscaEmProfundidade();
    void buscaEmLargura();

    void dijkstra(const std::string& origem, const std::string& destino);

    void a_star(const std::string& origem, const std::string& destino, std::map<std::string, int> heuristica);

    void to_dot(const std::string& filename);

private:

    const bool isDirecionado;
    std::map<std::string, std::shared_ptr<Vertice>> vertices;
};
} // namespace Grafos

#endif