
#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"


class Regador : Ferramenta{
    public:
      void aplica() override;

      Regador();
      ~Regador() override;

    private:
      int capacidade;

};

#endif
