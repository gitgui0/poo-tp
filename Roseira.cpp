#include "Roseira.h"
#include <iostream>

Roseira::Roseira() : Planta(25,25,'r',"Bonita") {};
Roseira::~Roseira(){ std::cout << "Desconstrutor roseira " << std::endl;}

void Roseira::cadaInstante(){ std::cout << "cada instante roseira" << std::endl;}


