#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"
#include <iostream>

class Cacto : public Planta {
    public:
      void cadaInstante(BocadoSolo* b) override;
      void multiplica(BocadoSolo *b, Jardim* j) override;
      BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;

      Cacto();
      Cacto(int agua, int nutri );
      ~Cacto() override;

};



#endif
