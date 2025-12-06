
#ifndef TESOURAPODA_H
#define TESOURAPODA_H

#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
    public:
      bool aplica(BocadoSolo* b, Jardim* j) override;
      std::string mostra() const override;
      TesouraPoda();
      ~TesouraPoda() override ;
};



#endif
