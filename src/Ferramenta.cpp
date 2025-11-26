#include "Ferramenta.h"

int Ferramenta::seq = 1;

Ferramenta::Ferramenta(const char letra) : EstaSolo(letra){
  numSerie = seq;
  seq++;
}

Ferramenta::~Ferramenta() = default;

std::ostream& operator<<(std::ostream& os, const Ferramenta* f) {
  os << f->mostra();
  return os;
}