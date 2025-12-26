#include "Settings.h"
#include "Regador.h"
#include <iostream>

using namespace std;

Regador::Regador() : Ferramenta('g'), capacidade(Settings::Regador::capacidade){};

bool Regador::aplica(BocadoSolo* b, Jardim* j) {
    b->setAgua(b->getAgua() + 10);

    capacidade = capacidade - 10;
    return capacidade <= 0;
}

std::string Regador::mostra() const {
    ostringstream oss;
    oss << "Regador - " << getNumSerie() <<  "\nCapacidade: " << capacidade << endl;
    return oss.str();
}
