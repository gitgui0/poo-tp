#include "Roseira.h"
#include "Settings.h"
#include <iostream>

Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua,
                            Settings::Roseira::inicial_nutrientes,'r',"Bonita") {};
Roseira::~Roseira(){ std::cout << "Desconstrutor roseira " << std::endl;}

void Roseira::cadaInstante(){ std::cout << "cada instante roseira" << std::endl;}


