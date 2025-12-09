#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"
#include <BocadoSolo.h>


class Adubo : public Ferramenta{
    public:
      bool aplica(BocadoSolo* b, Jardim* j) override;
      std::string mostra() const override;

      Ferramenta* clone() const{return new Adubo(*this);}

      Adubo();

      ~Adubo() override;

    private:
      int capacidade;
};



#endif
