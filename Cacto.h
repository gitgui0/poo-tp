#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"

class Cacto : public Planta {
    public:
      void cadaInstante() override;

      Cacto();
      ~Cacto() override;

};



#endif
