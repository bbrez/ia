#include <Util.h>

namespace Util {
std::string getOrigemDestino(std::ifstream& arquivo) {
    char buffer[20];

    arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '(');
    arquivo.getline(buffer, 20, ')');

    return std::string(buffer);
}

void readFile(Grafos::Grafo& g, Grafos::Heuristica& h, std::ifstream& arquivo) {
    char origem[20];
    char destino[20];
    char peso[10];

    while (!arquivo.eof()) {

        switch (arquivo.get()) {
        case 'p':
            {
                arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '(');
                arquivo.getline(origem, 20, ',');
                arquivo.getline(destino, 20, ',');
                arquivo.getline(peso, 20, ')');

                std::string ori(origem);
                std::string des(destino);
                int p = std::stoi(peso);

                g.adicionarAresta(ori, des, p);

                break;
            }
        case 'h':
            {
                arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '(');
                arquivo.getline(origem, 20, ',');
                arquivo.getline(destino, 20, ',');
                arquivo.getline(peso, 20, ')');

                std::string ori(origem);
                std::string des(destino);
                int p = std::stoi(peso);

                h.adicionarHeuristica(ori, des, p);

                break;
            }
        }
    }
}

} // namespace Util