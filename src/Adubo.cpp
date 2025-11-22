#include "./Adubo.h"
#include "./Settings.h"
#include <iostream>

using namespace std;

Adubo::Adubo() : Ferramenta('a'), capacidade(Settings::Adubo::capacidade){};
Adubo::~Adubo() = default;

void Adubo::aplica() { cout << "Aplica pacote adubo" << endl; }

string Adubo::mostra() {
    ostringstream oss;
    oss << "Adubo - " << getNumSerie() <<  "\nCapacidade: " << capacidade << endl;
    return oss.str();
}
