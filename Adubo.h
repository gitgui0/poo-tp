#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"

class Adubo : public Ferramenta{
    public:
      void aplica() override;

      Adubo();

      ~Adubo() override;

    private:
      int capacidade;
};



#endif
