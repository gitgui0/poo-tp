
#ifndef REGADOR_H
#define REGADOR_H

#include <BocadoSolo.h>

#include "Ferramenta.h"


class Regador : public Ferramenta{
    public:
      bool aplica(BocadoSolo* b, Jardim* j) override;
      std::string mostra() const override;

      Regador();
      ~Regador() override;

    private:
      int capacidade;

};

#endif
