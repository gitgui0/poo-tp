//
// Created by deepz on 22/10/2025.
//

#include "Ferramenta.h"

int Ferramenta::seq = 1;

Ferramenta::Ferramenta(const char letra) : EstaSolo(letra){
  numSerie = seq;
  seq++;
}
