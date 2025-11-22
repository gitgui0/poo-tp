#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"

class Adubo : public Ferramenta{
    public:
      void aplica() override;
      std::string mostra() override;

      Adubo();

      ~Adubo() override;

    private:
      int capacidade;
};



#endif
