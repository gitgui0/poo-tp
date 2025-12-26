#include "Ferramenta.h"
#include "Adubo.h"
#include "Regador.h"
#include "TesouraPoda.h"
#include "AceleradorCrescimento.h"

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

Ferramenta *Ferramenta::criar(char ferr) {
  Ferramenta* novaFerramenta = nullptr;
  switch (tolower(ferr)) {
    case 'g':
      novaFerramenta = new Regador();
    break;
    case 'a':
      novaFerramenta = new Adubo();
    break;
    case 't':
      novaFerramenta = new TesouraPoda();
    break;
    case 'z':
      novaFerramenta = new AceleradorCrescimento();
    break;
    default:
      throw std::runtime_error("Tipo de ferramenta invalida. Use g, a, t, ou z.");
  }

  return novaFerramenta;
}
