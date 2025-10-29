#include "Planta.h"

Planta::Planta(int agua, int nutrientes, char letra, const std::string& beleza) :
    agua(agua), nutrientes(nutrientes), EstaSolo(letra)
{
  if(beleza != "Feia" and beleza != "Bonita" and beleza != "Neutra")
    throw 1; // TODO: mudar este 1, para alguma coisa sentido
  this->beleza = beleza;
  this->countInstantes = 0;
}