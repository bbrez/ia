#include <Util.h>

#include <Grafo/Grafo.h>
#include <Grafo/Heuristica.h>
#include <Grafo/Caminho.h>

#include <iostream>
#include <fstream>

auto main(int argc, char** argv) -> int {
    if (argc < 2) {
        std::cout << "Uso: " << argv[0] << " <arquivo>" << std::endl;
        return 1;
    }

    Grafos::Grafo g(false);
    Grafos::Heuristica h;

    std::ifstream entrada(argv[1]);
    std::string vOrigem = Util::getOrigemDestino(entrada);
    std::string vDestino = Util::getOrigemDestino(entrada);
    Util::readFile(g, h, entrada);

    std::cout << "Grafo:" << std::endl;
    g.imprimir();
    std::cout << std::endl;

    std::cout << "============================================" << std::endl;
    std::cout << "Pior Caso entre Largura e Profundidade:" << std::endl;
    Grafos::Caminho c1 = g.piorCaso(vOrigem, vDestino).value();

    std::cout << std::endl;
    std::cout << "Caminho: " << std::endl;
    c1.imprimir();
    std::cout << std::endl;

    std::cout << "Comprimento: " << c1.getComprimento() << std::endl;
    std::cout << "Distancia: " << c1.getDistancia() << std::endl;
    std::cout << "Vertices visitados na busca: " << c1.getVisitados() << std::endl;
    std::cout << std::endl;

    std::cout << "============================================" << std::endl;
    std::cout << "Algoritmo de Dijkstra:" << std::endl;
    Grafos::Caminho c2 = g.dijkstra(vOrigem, vDestino).value();

    std::cout << std::endl;
    std::cout << "Caminho: " << std::endl;
    c2.imprimir();
    std::cout << std::endl;

    std::cout << "Comprimento: " << c2.getComprimento() << std::endl;
    std::cout << "Distancia: " << c2.getDistancia() << std::endl;
    std::cout << "Vertices visitados na busca: " << c2.getVisitados() << std::endl;
    std::cout << std::endl;

    std::cout << "============================================" << std::endl;
    std::cout << "Algoritmo de A*:" << std::endl;
    Grafos::Caminho c3 = g.a_star(vOrigem, vDestino, h).value();

    std::cout << std::endl;
    std::cout << "Caminho: " << std::endl;
    c3.imprimir();
    std::cout << std::endl;

    std::cout << "Comprimento: " << c3.getComprimento() << std::endl;
    std::cout << "Distancia: " << c3.getDistancia() << std::endl;
    std::cout << "Vertices visitados na busca: " << c3.getVisitados() << std::endl;
    std::cout << std::endl;


    return 0;
}