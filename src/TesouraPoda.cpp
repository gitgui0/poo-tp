
#include "TesouraPoda.h"

#include <iostream>
using namespace std;

TesouraPoda::TesouraPoda() : Ferramenta('t') {};
TesouraPoda::~TesouraPoda() = default;

void TesouraPoda::aplica() { std::cout << "Aplica tesoura poda" << std::endl; }

std::string TesouraPoda::mostra() const {
    ostringstream oss;
    oss << "Tesoura de Poda - " << getNumSerie() << endl;
    return oss.str();
}
