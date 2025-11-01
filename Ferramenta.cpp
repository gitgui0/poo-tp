#include "Ferramenta.h"

int Ferramenta::seq = 1;

Ferramenta::Ferramenta(const char letra) : EstaSolo(letra){
  numSerie = seq;
  seq++;
}

Ferramenta::~Ferramenta() = default;
