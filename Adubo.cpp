#include "Adubo.h"
#include <iostream>

Adubo::Adubo() : Ferramenta('a'), capacidade(100){};
Adubo::~Adubo() = default;

void Adubo::aplica() { std::cout << "Aplica pacote adubo" << std::endl; }
