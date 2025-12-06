#include "./Adubo.h"
#include "./Settings.h"
#include <iostream>

using namespace std;

Adubo::Adubo() : Ferramenta('a'), capacidade(Settings::Adubo::capacidade){};
Adubo::~Adubo() = default;

bool Adubo::aplica(BocadoSolo* b, Jardim* j) {
    b->setNutrientes(b->getNutrientes() + 10);

    capacidade = capacidade - 10;
    return capacidade <= 0;
}

string Adubo::mostra() const {
    ostringstream oss;
    oss << "Adubo - " << getNumSerie() <<  "\nCapacidade: " << capacidade << endl;
    return oss.str();
}
