#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"

class ErvaDaninha : public Planta{
    public:
      void cadaInstante() override;

      ErvaDaninha();
      ~ErvaDaninha();

};



#endif
