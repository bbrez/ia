#ifndef HEURISTICA_H
#define HEURISTICA_H

#include <map>
#include <string>

namespace Grafos {
class Heuristica {
public:

    Heuristica() = default;
    ~Heuristica() = default;

    void adicionarHeuristica(const std::string& origem, const std::string& destino, int peso);

    int getHeuristica(const std::string& origem, const std::string& destino);

private:

    std::map<std::string, std::map<std::string, int>> heuristica;
};
} // namespace Grafos

#endif