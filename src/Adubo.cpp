#include "./Adubo.h"
#include "./Settings.h"
#include <iostream>

Adubo::Adubo() : Ferramenta('a'), capacidade(Settings::Adubo::capacidade){};
Adubo::~Adubo() = default;

void Adubo::aplica() { std::cout << "Aplica pacote adubo" << std::endl; }
