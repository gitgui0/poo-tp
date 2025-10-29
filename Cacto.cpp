#include "Cacto.h"
#include <iostream>

Cacto::Cacto() : Planta(0,0,'c',"Neutra") {};
Cacto::~Cacto(){ std::cout << "Desconstrutor cacto " << std::endl;}

void Cacto::cadaInstante(){ std::cout << "cada instante cacto" << std::endl;}


