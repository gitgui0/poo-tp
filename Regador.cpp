
#include "Regador.h"
#include <iostream>

Regador::Regador() : Ferramenta('g'), capacidade(200){};

void Regador::aplica(){ std::cout << "Aplica regador" << std::endl; }
