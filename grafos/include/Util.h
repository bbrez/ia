#ifndef UTIL_H
#define UTIL_H

#include <Grafo/Grafo.h>
#include <Grafo/Heuristica.h>

#include <fstream>

namespace Util {
std::string getOrigemDestino(std::ifstream& arquivo);

void readFile(Grafos::Grafo& g, Grafos::Heuristica& h, std::ifstream& arquivo);
} // namespace Util
#endif