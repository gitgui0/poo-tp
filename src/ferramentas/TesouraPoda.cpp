
#include "TesouraPoda.h"

#include <BocadoSolo.h>
#include <iostream>
#include <Planta.h>
using namespace std;

TesouraPoda::TesouraPoda() : Ferramenta('t') {};
TesouraPoda::~TesouraPoda() = default;

bool TesouraPoda::aplica(BocadoSolo* b, Jardim* j) {
    Planta *p = b->getPlanta();
    if (p==nullptr)
        return false;

    if (p->getBeleza() == "Feia")
        b->setPlanta(nullptr);
    return false;
}

std::string TesouraPoda::mostra() const {
    ostringstream oss;
    oss << "Tesoura de Poda - " << getNumSerie() << endl;
    return oss.str();
}
