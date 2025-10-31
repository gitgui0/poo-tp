#include "Settings.h"
#include "Regador.h"
#include <iostream>

Regador::Regador() : Ferramenta('g'), capacidade(Settings::Regador::capacidade){};
Regador::~Regador() = default;
void Regador::aplica(){ std::cout << "Aplica regador" << std::endl; }
