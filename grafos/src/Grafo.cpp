#include <Grafo/Cor.h>
#include <Grafo/Grafo.h>
#include <Grafo/Caminho.h>

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <memory>

#include <functional>
#include <set>
#include <queue>
#include <stack>
#include <utility>

#define PRINT_INFO

namespace Grafos {
Grafo::Grafo(bool isDirecionado) : isDirecionado(isDirecionado) {}

Grafo::~Grafo() {}

void Grafo::adicionarVertice(const std::string& nome) {
    if (vertices.find(nome) == vertices.end()) {
        vertices[nome] = std::make_shared<Vertice>(nome);
    }
}

void Grafo::adicionarAresta(const std::string& origem, const std::string& destino, int peso) {
    if (vertices.find(origem) == vertices.end()) {
        adicionarVertice(origem);
    }

    if (vertices.find(destino) == vertices.end()) {
        adicionarVertice(destino);
    }

    auto aresta = std::make_shared<Aresta>(peso);
    aresta->setOrigem(vertices[origem]);
    aresta->setDestino(vertices[destino]);

    vertices[origem]->adicionarAresta(aresta);

    if (!isDirecionado) {
        auto oposta = std::make_shared<Aresta>(peso);
        oposta->setOrigem(vertices[destino]);
        oposta->setDestino(vertices[origem]);

        vertices[destino]->adicionarAresta(oposta);
    }
}

void Grafo::imprimir() {
    for (auto& [nome, vertice] : vertices) {
        std::cout << "Vertice: " << nome << std::endl;

        for (auto& [nomeAresta, aresta] : vertice->getArestas()) {
            std::cout << "\tAresta: " << nomeAresta << " - Peso: " << aresta->getPeso() << std::endl;
        }
    }
}

std::optional<Caminho> Grafo::buscaEmProfundidade(const std::string& origem, const std::string& destino) {
    if (vertices.find(origem) == vertices.end() || vertices.find(destino) == vertices.end()) {
        std::cout << "Origem ou destino nao encontrados" << std::endl;

        return std::nullopt;
    }

    Caminho caminho;
    std::map<std::string, std::string> antecessores;
    std::map<std::string, Cor> cores;

    for (auto& [nome, vertice] : vertices) {
        cores[nome] = Cor::BRANCO;
    }

    std::stack<std::shared_ptr<Vertice>> pilha;
    pilha.push(vertices[origem]);

    std::cout << "Vertice inicial: " << origem << std::endl;
    std::cout << "Vertice final: " << destino << std::endl;

    while (!pilha.empty()) {
        auto vertice = pilha.top();
        pilha.pop();
        caminho.incrementarVisitados();

        std::cout << "Visitando vertice: " << vertice->getNome() << std::endl;

        if (vertice->getNome() == destino) {
            std::cout << "Caminho encontrado" << std::endl;

            caminho.push_back(vertice);

            while (vertice->getNome() != origem) {
                vertice = vertices[antecessores[vertice->getNome()]];
                caminho.push_back(vertice);
            }

            std::reverse(caminho.begin(), caminho.end());
            return caminho;
        }

        if (cores[vertice->getNome()] == Cor::BRANCO) {
            cores[vertice->getNome()] = Cor::CINZA;

            for (auto& [nomeAresta, aresta] : vertice->getArestas()) {
                if (cores[aresta->getDestino()->getNome()] == Cor::BRANCO) {
                    std::cout << "\tEmpilhando vertice: " << aresta->getDestino()->getNome() << std::endl;

                    antecessores[aresta->getDestino()->getNome()] = vertice->getNome();
                    pilha.push(aresta->getDestino());
                }
            }
        }

        cores[vertice->getNome()] = Cor::PRETO;
    }

    std::cout << "Caminho nao encontrado" << std::endl;
    return std::nullopt;
}

std::optional<Caminho> Grafo::buscaEmLargura(const std::string& origem, const std::string& destino) {
    if (vertices.find(origem) == vertices.end() || vertices.find(destino) == vertices.end()) {
        std::cout << "Origem ou destino nao encontrados" << std::endl;

        return std::nullopt;
    }

    Caminho caminho;
    std::map<std::string, std::string> antecessores;
    std::map<std::string, Cor> cores;

    for (auto& [nome, vertice] : vertices) {
        cores[nome] = Cor::BRANCO;
    }

    std::queue<std::shared_ptr<Vertice>> fila;
    fila.push(vertices[origem]);

    std::cout << "Vertice inicial: " << origem << std::endl;

    while (!fila.empty()) {
        auto vertice = fila.front();
        fila.pop();
        caminho.incrementarVisitados();

        std::cout << "Visitando vertice: " << vertice->getNome() << std::endl;

        if (vertice->getNome() == destino) {
            std::cout << "Caminho encontrado" << std::endl;

            caminho.push_back(vertice);

            while (vertice->getNome() != origem) {
                vertice = vertices[antecessores[vertice->getNome()]];
                caminho.push_back(vertice);
            }

            std::reverse(caminho.begin(), caminho.end());
            return caminho;
        }

        if (cores[vertice->getNome()] == Cor::BRANCO) {
            cores[vertice->getNome()] = Cor::CINZA;

            for (auto& [nomeAresta, aresta] : vertice->getArestas()) {
                if (cores[aresta->getDestino()->getNome()] == Cor::BRANCO) {
                    std::cout << "\tEnfileirando vertice " << aresta->getDestino()->getNome() << std::endl;

                    antecessores[aresta->getDestino()->getNome()] = vertice->getNome();
                    fila.push(aresta->getDestino());
                }
            }
        }

        cores[vertice->getNome()] = Cor::PRETO;
    }

    std::cout << "Caminho nao encontrado" << std::endl;
    return std::nullopt;
}

std::optional<Caminho> Grafo::piorCaso(const std::string& origem, const std::string& destino) {
    std::cout << "Busca em profundidade:" << std::endl;
    auto profundidade = this->buscaEmProfundidade(origem, destino);
    std::cout << std::endl << "******************************" << std::endl;
    std::cout << "Busca em largura:" << std::endl;
    auto largura = this->buscaEmLargura(origem, destino);

    if (profundidade.has_value() && largura.has_value()) {
        if (profundidade.value().size() > largura.value().size()) {
            std::cout << "Pior caso: Busca em profundidade" << std::endl;
            return profundidade;
        } else {
            std::cout << "Pior caso: Busca em largura" << std::endl;
            return largura;
        }
    } else if (profundidade.has_value()) {
        std::cout << "Pior caso: Busca em profundidade (largura não encontrou caminho)" << std::endl;
        return profundidade;
    } else if (largura.has_value()) {
        std::cout << "Pior caso: Busca em largura (profundidade não encontrou caminho)" << std::endl;
        return largura;
    } else {
        std::cout << "Pior caso: Nenhum caminho encontrado" << std::endl;
        return std::nullopt;
    }
}

std::optional<Caminho> Grafo::dijkstra(const std::string& origem, const std::string& destino) {
    struct dijkstra_info {
        int distancia;
        std::string verticeAnterior;
        Cor cor;
    };

    Caminho caminho;
    std::map<std::string, dijkstra_info> info;

    for (auto& [nome, vertice] : vertices) {
        info[nome] = {INT_MAX, "", Cor::BRANCO};
    }

    info[origem].distancia = 0;

    // fila de prioridade para pegar o menor caminho
    // o primeiro elemento da fila é o menor peso
    std::priority_queue<std::pair<int, std::string>,               // pair<distancia, vertice>
                        std::vector<std::pair<int, std::string>>,  // container da fila
                        std::greater<std::pair<int, std::string>>> // comparação
        fila;

    fila.push({0, origem});

    std::cout << "Vertice inicial: " << origem << std::endl;

    while (!fila.empty()) {
        auto [distancia, vertice] = fila.top();
        fila.pop();
        caminho.incrementarVisitados();

        std::cout << "Visitando vertice " << vertice << std::endl;

        if (info[vertice].cor == Cor::BRANCO) {
            info[vertice].cor = Cor::CINZA;

            if (vertice == destino) {
                std::cout << "Destino encontrado" << std::endl;

                caminho.push_back(vertices[vertice]);

                while (info[vertice].verticeAnterior != "") {
                    vertice = info[vertice].verticeAnterior;
                    caminho.push_back(vertices[vertice]);
                }

                std::reverse(caminho.begin(), caminho.end());
                return caminho;
            }

            for (auto& [nome, aresta] : vertices[vertice]->getArestas()) {
                auto distanciaAtual = info[vertice].distancia + aresta->getPeso();

                if (distanciaAtual < info[aresta->getDestino()->getNome()].distancia) {
                    info[aresta->getDestino()->getNome()].distancia = distanciaAtual;
                    info[aresta->getDestino()->getNome()].verticeAnterior = vertice;
                    fila.push({distanciaAtual, aresta->getDestino()->getNome()});

                    std::cout << "\tEnfileirando aresta " << nome << std::endl;
                }
            }
        }
    }

    std::cout << "Caminho nao encontrado" << std::endl;
    return std::nullopt;
}

std::optional<Caminho> Grafo::a_star(const std::string& origem, const std::string& destino, Heuristica heuristica) {
    struct a_star_info {
        int distancia;
        std::string verticeAnterior;
        Cor cor;
    };

    std::map<std::string, a_star_info> info;

    for (auto& [nome, vertice] : vertices) {
        info[nome] = {INT_MAX, "", Cor::BRANCO};
    }

    info[origem].distancia = 0;

    // fila de prioridade para pegar o menor caminho
    // o primeiro elemento da fila é o menor peso
    std::priority_queue<std::pair<int, std::string>,               // pair<distancia, vertice>
                        std::vector<std::pair<int, std::string>>,  // container da fila
                        std::greater<std::pair<int, std::string>>> // comparação
        fila;

    fila.push({0, origem});

    std::cout << "Vertice inicial: " << origem << std::endl;

    Caminho caminho;
    while (!fila.empty()) {
        auto [distancia, vertice] = fila.top();
        fila.pop();
        caminho.incrementarVisitados();


        std::cout << "Visitando vertice " << vertice << std::endl;

        if (info[vertice].cor == Cor::BRANCO) {
            info[vertice].cor = Cor::CINZA;

            if (vertice == destino) {
                std::cout << "Destino encontrado" << std::endl;

                caminho.push_back(vertices[vertice]);

                while (info[vertice].verticeAnterior != "") {
                    vertice = info[vertice].verticeAnterior;
                    caminho.push_back(vertices[vertice]);
                }

                std::reverse(caminho.begin(), caminho.end());
                return caminho;
            }

            for (auto& [nome, aresta] : vertices[vertice]->getArestas()) {
                auto distanciaAtual = info[vertice].distancia + aresta->getPeso();

                if (distanciaAtual < info[aresta->getDestino()->getNome()].distancia) {
                    info[aresta->getDestino()->getNome()].distancia = distanciaAtual;
                    info[aresta->getDestino()->getNome()].verticeAnterior = vertice;
                    fila.push({distanciaAtual + heuristica.getHeuristica(aresta->getDestino()->getNome(), destino),
                               aresta->getDestino()->getNome()});

                    std::cout << "\tEnfileirando aresta " << nome << std::endl;
                }
            }
        }
    }

    std::cout << "Caminho nao encontrado" << std::endl;
    return std::nullopt;
}

/*
void Grafo::to_dot(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Erro ao abrir arquivo" << std::endl;
        return;
    }

    if (vertices.empty()) {
        std::cout << "Grafo vazio" << std::endl;
        return;
    }

    if (this->isDirecionado) {
        file << "digraph G {" << std::endl;
    } else {
        file << "graph G {" << std::endl;
    }

    file << "    layout = neato;" << std::endl;
    file << "    sep = 1.5;" << std::endl;
    file << "    overlap = false;" << std::endl;

    for (auto& [nome, vertice] : vertices) {
        file << std::format("\t{} [label=\"{}\"]", nome, nome) << std::endl;
    }

    std::set<std::pair<std::string, std::string>> arestasInseridas;

    for (auto& [nome, vertice] : vertices) {
        for (auto& [nomeAresta, aresta] : vertice->getArestas()) {
            if (arestasInseridas.find({nome, nomeAresta}) != arestasInseridas.end()) {
                continue;
            }
            if (this->isDirecionado) {
                file << std::format("\t{} -> {} [xlabel=\"{}\"]", nome, nomeAresta, aresta->getPeso()) << std::endl;
                arestasInseridas.insert({nome, nomeAresta});
            } else {
                file << std::format("\t{} -- {} [xlabel=\"{}\"]", nome, nomeAresta, aresta->getPeso()) << std::endl;
                arestasInseridas.insert({nome, nomeAresta});
                arestasInseridas.insert({nomeAresta, nome});
            }
        }
    }

    file << "}" << std::endl;

    file.close();

    std::cout << "Arquivo gerado com sucesso" << std::endl;
}*/

} // namespace Grafos