#include <Grafo/Cor.h>
#include <Grafo/Grafo.h>
#include <Grafo/Caminho.h>

#include <iostream>
#include <fstream>
#include <format>
#include <optional>
#include <string>
#include <memory>

#include <functional>
#include <set>
#include <queue>
#include <stack>
#include <utility>

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

void Grafo::imprimirGrafo() {
    for (auto& [nome, vertice] : vertices) {
        std::cout << std::format("Vertice: {}", nome) << std::endl;

        for (auto& [nomeAresta, aresta] : vertice->getArestas()) {
            std::cout << std::format("\tAresta: {} - Peso: {}", nomeAresta, aresta->getPeso()) << std::endl;
        }
    }
}

std::optional<Caminho> Grafo::buscaEmProfundidade(const std::string& origem, const std::string& destino) {
    if (vertices.find(origem) == vertices.end() || vertices.find(destino) == vertices.end()) {
        std::cout << "Origem ou destino nao encontrados" << std::endl;
        return std::nullopt;
    }

    Caminho caminho;
    std::map<std::string, Cor> cores;

    for (auto& [nome, vertice] : vertices) {
        cores[nome] = Cor::BRANCO;
    }

    std::stack<std::shared_ptr<Vertice>> pilha;
    pilha.push(vertices[origem]);

    while (!pilha.empty()) {
        auto vertice = pilha.top();
        pilha.pop();

        if (cores[vertice->getNome()] == Cor::BRANCO) {
            caminho.push_back(vertice);
            cores[vertice->getNome()] = Cor::CINZA;

            if (vertice->getNome() == destino) {
                return caminho;
            }

            for (auto& [nome, aresta] : vertice->getArestas()) {
                pilha.push(aresta->getDestino());
            }
        }
    }

    return std::nullopt;
}

std::optional<Caminho> Grafo::buscaEmLargura(const std::string& origem, const std::string& destino) {
    if (vertices.find(origem) == vertices.end() || vertices.find(destino) == vertices.end()) {
        std::cout << "Origem ou destino nao encontrados" << std::endl;
        return std::nullopt;
    }

    Caminho caminho;
    std::map<std::string, Cor> cores;

    for (auto& [nome, vertice] : vertices) {
        cores[nome] = Cor::BRANCO;
    }

    std::queue<std::shared_ptr<Vertice>> fila;
    fila.push(vertices[origem]);

    while (!fila.empty()) {
        auto vertice = fila.front();
        fila.pop();

        if (cores[vertice->getNome()] == Cor::BRANCO) {
            caminho.push_back(vertice);
            cores[vertice->getNome()] = Cor::CINZA;

            if (vertice->getNome() == destino) {
                return caminho;
            }

            for (auto& [nome, aresta] : vertice->getArestas()) {
                fila.push(aresta->getDestino());
            }
        }
    }

    return std::nullopt;
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

    while (!fila.empty()) {
        auto [distancia, vertice] = fila.top();
        fila.pop();

        if (info[vertice].cor == Cor::BRANCO) {
            info[vertice].cor = Cor::CINZA;

            if (vertice == destino) {
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
                }
            }
        }
    }

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

    while (!fila.empty()) {
        auto verticeAtual = fila.top();
        fila.pop();

        if (info[verticeAtual.second].cor == Cor::PRETO) {
            continue;
        }

        info[verticeAtual.second].cor = Cor::PRETO;

        for (auto& [nomeAresta, aresta] : vertices[verticeAtual.second]->getArestas()) {
            if (info[nomeAresta].cor == Cor::PRETO) {
                continue;
            }

            if (info[nomeAresta].distancia > info[verticeAtual.second].distancia + aresta->getPeso()) {
                info[nomeAresta].distancia = info[verticeAtual.second].distancia + aresta->getPeso();
                info[nomeAresta].verticeAnterior = verticeAtual.second;
                fila.push({info[nomeAresta].distancia + heuristica.getHeuristica(nomeAresta, destino), nomeAresta});
            }
        }
    }

    std::cout << std::format("Distancia de {} para {}: {}", origem, destino, info[destino].distancia) << std::endl;

    std::stack<std::string> caminho;
    caminho.push(destino);
    while (info[caminho.top()].verticeAnterior != "") {
        caminho.push(info[caminho.top()].verticeAnterior);
    }

    std::string caminhoString;
    while (!caminho.empty()) {
        caminhoString += caminho.top();
        caminho.pop();

        if (!caminho.empty()) {
            caminhoString += " -> ";
        }
    }

    std::cout << std::format("Caminho: {}", caminhoString) << std::endl;

    return std::nullopt;
}

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
}

} // namespace Grafos