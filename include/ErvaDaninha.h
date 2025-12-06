#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"
#include <iostream>

class ErvaDaninha : public Planta{
    public:
    bool cadaInstante(BocadoSolo* b) override;
      void multiplica(BocadoSolo *b, Jardim* j) override;
      BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;

      ErvaDaninha();
      ErvaDaninha(int agua, int nutrientes);
      ~ErvaDaninha();

    private:
       int instantesAtuais;
       int instanteMulti;

};



#endif
