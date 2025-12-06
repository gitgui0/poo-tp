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


void Planta::colocarAgua(int agua) {
    if (agua>0)
        this->agua = agua;
    else
        this->agua = 0;
}
void Planta::colocarNutrientes(int nutrientes) {
    if (nutrientes > 0)
        this->nutrientes = nutrientes;
    else
        this->nutrientes = 0;
}