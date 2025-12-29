#include "Settings.h"
#include "Regador.h"
#include <sstream>
#include "BocadoSolo.h"

using namespace std;

Regador::Regador() : Ferramenta('g'), capacidade(Settings::Regador::capacidade){}

bool Regador::aplica(BocadoSolo* b, Jardim* j) {
    int dose = Settings::Regador::dose;
    b->setAgua(b->getAgua() + dose);

    capacidade -= dose;
    return capacidade <= 0;
}

std::string Regador::mostra() const {
    ostringstream oss;
    oss << getNumSerie() << " - Regador - Capacidade - " << capacidade << endl;
    return oss.str();
}
