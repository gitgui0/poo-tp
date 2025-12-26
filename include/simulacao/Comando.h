
#ifndef COMANDO_H
#define COMANDO_H

#include <sstream>
#include "Simulador.h"


class Comando {
    public:
      virtual void executa(Simulador &sim, std::istringstream & params) const = 0;
      virtual const string getNome() = 0;
      Comando() = default;
      ~Comando() = default;
};



#endif
