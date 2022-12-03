#include <Grafo/Grafo.h>

#include <iostream>
#include <ostream>

auto main() -> int {
    Grafos::Grafo g(false);

    g.adicionarVertice("0");
    g.adicionarVertice("1");
    g.adicionarVertice("2");
    g.adicionarVertice("3");
    g.adicionarVertice("4");
    g.adicionarVertice("5");
    g.adicionarVertice("6");

    g.adicionarAresta("0", "2", 8);
    g.adicionarAresta("0", "3", 5);
    g.adicionarAresta("0", "5", 11);
    g.adicionarAresta("1", "3", 2);
    g.adicionarAresta("1", "4", 18);
    g.adicionarAresta("2", "3", 7);
    g.adicionarAresta("2", "4", 3);
    g.adicionarAresta("2", "5", 4);
    g.adicionarAresta("4", "5", -1);
    g.adicionarAresta("4", "6", 5);
    g.adicionarAresta("5", "6", 17);

    std::cout << "Grafo: " << std::endl;
    g.imprimirGrafo();

    std::cout << std::endl << "Busca em profundidade: " << std::endl;
    g.buscaEmProfundidade();

    std::cout << std::endl << "Busca em largura: " << std::endl;
    g.buscaEmLargura();

    std::cout << std::endl << "Dijkstra: " << std::endl;
    g.dijkstra("0", "6");

    std::cout << std::endl << "A* (heuristica: distancia euclidiana): " << std::endl;
    std::map<std::string, int> heuristica = {
        {"0", 10},
        {"1",  8},
        {"2",  7},
        {"3",  6},
        {"4",  5},
        {"5",  4},
        {"6",  0}
    };

    g.a_star("0", "6", heuristica);

    g.to_dot("grafo.dot");

    return 0;
}