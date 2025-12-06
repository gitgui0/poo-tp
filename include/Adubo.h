#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"
#include <BocadoSolo.h>


class Adubo : public Ferramenta{
    public:
      bool aplica(BocadoSolo* b, Jardim* j) override;
      std::string mostra() const override;

      Adubo();

      ~Adubo() override;

    private:
      int capacidade;
};



#endif
