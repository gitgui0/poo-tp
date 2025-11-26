
#ifndef TESOURAPODA_H
#define TESOURAPODA_H

#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
    public:
      void aplica() override;
      std::string mostra() const override;
      TesouraPoda();
      ~TesouraPoda() override ;
};



#endif
