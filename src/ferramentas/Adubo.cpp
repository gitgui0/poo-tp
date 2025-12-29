#include "./Adubo.h"
#include "./Settings.h"
#include <iostream>

using namespace std;

Adubo::Adubo() : Ferramenta('a'), capacidade(Settings::Adubo::capacidade){};

bool Adubo::aplica(BocadoSolo* b, Jardim* j) {
    int dose = Settings::Adubo::dose;
    b->setNutrientes(b->getNutrientes() + dose);

    capacidade -= dose;
    return capacidade <= 0;
}

string Adubo::mostra() const {
    ostringstream oss;
    oss << getNumSerie() << " - Adubo - Capacidade - " << capacidade << endl;
    return oss.str();
}
