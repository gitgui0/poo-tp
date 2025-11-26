#include "AceleradorCrescimento.h"
#include <iostream>

using namespace std;

AceleradorCrescimento::AceleradorCrescimento() :
    Ferramenta('z'),
    capacidade(15)
{}

AceleradorCrescimento::~AceleradorCrescimento() = default;

void AceleradorCrescimento::aplica() {
    cout << "Acelerador de Crescimento aplicado: Aceleração de 3 instantes (A implementar na Meta 2)." << endl;
}

std::string AceleradorCrescimento::mostra() const {
    ostringstream oss;
    oss << "Acelerador de Crescimento -" << getNumSerie() <<  "\nCapacidade: " << capacidade << endl;
    return oss.str();
}
