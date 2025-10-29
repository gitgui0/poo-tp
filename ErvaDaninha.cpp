#include "ErvaDaninha.h"
#include <iostream>

ErvaDaninha::ErvaDaninha() :
    Planta(5,5,'e',"Feia")
{};

ErvaDaninha::~ErvaDaninha(){ std::cout << "Destructor Erva Daninha" << std::endl;}

void ErvaDaninha::cadaInstante(){ std::cout << "Cada instante Erva Daninha" << std::endl;}

