#include "Settings.h"
#include "Regador.h"
#include <iostream>

using namespace std;

Regador::Regador() : Ferramenta('g'), capacidade(Settings::Regador::capacidade){};
Regador::~Regador() = default;
void Regador::aplica(){ std::cout << "Aplica regador" << std::endl; }

std::string Regador::mostra() {
    ostringstream oss;
    oss << "Acelerador de Crescimento - " << getNumSerie() <<  "\nCapacidade: " << capacidade << endl;
    return oss.str();
}
