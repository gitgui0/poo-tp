#include "Planta.h"
#include <iostream>

#include "Cacto.h"
#include "ErvaDaninha.h"
#include "Orquidea.h"
#include "Roseira.h"

Planta::Planta(int agua, int nutrientes, char letra, const std::string& beleza) :
    agua(agua), nutrientes(nutrientes), EstaSolo(letra)
{
  if(beleza != "Feia" and beleza != "Bonita" and beleza != "Neutra")
    throw std::runtime_error("beleza invalida");
  this->beleza = beleza;
  this->countInstantes = 0;
}

Planta::~Planta() = default;

Planta* Planta::criar(char planta) {
    Planta* novaPlanta = nullptr;
    switch (tolower(planta)) {
        case 'c':
            novaPlanta = new Cacto();
        break;
        case 'e':
            novaPlanta = new ErvaDaninha();
        break;
        case 'x':
            novaPlanta = new Orquidea();
        break;
        case 'r':
            novaPlanta = new Roseira();
        break;
        default:
            throw std::runtime_error("Tipo de planta invalida. Cacto - c, Erva Daninha - e, Orquidea - x, Roseira - r ");
    }
    return novaPlanta;
}