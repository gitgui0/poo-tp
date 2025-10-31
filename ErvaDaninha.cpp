#include "ErvaDaninha.h"
#include "Settings.h"

#include <iostream>


ErvaDaninha::ErvaDaninha() :
    Planta(Settings::ErvaDaninha::inicial_agua,Settings::ErvaDaninha::inicial_nutrientes,
        'e',"Feia")
{};

ErvaDaninha::~ErvaDaninha(){ std::cout << "Destructor Erva Daninha" << std::endl;}

void ErvaDaninha::cadaInstante(){ std::cout << "Cada instante Erva Daninha" << std::endl;}

