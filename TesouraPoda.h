
#ifndef TESOURAPODA_H
#define TESOURAPODA_H

#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
    public:
      void aplica() override;
      TesouraPoda();
      ~TesouraPoda() override ;
};



#endif //TESOURAPODA_H
