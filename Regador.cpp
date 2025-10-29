
#include "Regador.h"
#include <iostream>

Regador::Regador() : Ferramenta('g'), capacidade(200){};
Regador::~Regador() = default;
void Regador::aplica(){ std::cout << "Aplica regador" << std::endl; }
