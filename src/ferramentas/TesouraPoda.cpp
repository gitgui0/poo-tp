
#include "TesouraPoda.h"

#include <sstream>
#include "BocadoSolo.h"
#include "Planta.h"

using namespace std;

TesouraPoda::TesouraPoda() : Ferramenta('t') {}

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
    oss << getNumSerie() << " - Tesoura de Poda" << endl;
    return oss.str();
}
