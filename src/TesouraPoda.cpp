
#include "TesouraPoda.h"

#include <iostream>

TesouraPoda::TesouraPoda() : Ferramenta('t') {};
TesouraPoda::~TesouraPoda() = default;

void TesouraPoda::aplica() { std::cout << "Aplica tesoura poda" << std::endl; }
