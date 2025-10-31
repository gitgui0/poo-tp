#include "Planta.h"
#include <iostream>

Planta::Planta(int agua, int nutrientes, char letra, const std::string& beleza) :
    agua(agua), nutrientes(nutrientes), EstaSolo(letra)
{
  if(beleza != "Feia" and beleza != "Bonita" and beleza != "Neutra")
    throw std::runtime_error("beleza invalida");
  this->beleza = beleza;
  this->countInstantes = 0;
}

Planta::~Planta() = default;

void Planta::obterAgua(int agua){ std::cout << "Obter agua: " << agua << std::endl;}
void Planta::obterNutrientes(int nutrientes){ std::cout << "Obter nutrientes: " << nutrientes << std::endl;}

void Planta::colocarAgua(int agua){ std::cout << "Colocar agua: " << agua << std::endl;}
void Planta::colocarNutrientes(int nutrientes){ std::cout << "Colocar nutrientes: " << nutrientes << std::endl;}