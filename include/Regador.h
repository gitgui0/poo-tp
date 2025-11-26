
#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"


class Regador : public Ferramenta{
    public:
      void aplica() override;
      std::string mostra() const override;

      Regador();
      ~Regador() override;

    private:
      int capacidade;

};

#endif
