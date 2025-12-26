
#ifndef TESOURAPODA_H
#define TESOURAPODA_H

#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
    public:
        TesouraPoda();
        ~TesouraPoda() override = default;

        bool aplica(BocadoSolo* b, Jardim* j) override;
        std::string mostra() const override;

        Ferramenta* clone() const override {return new TesouraPoda(*this);}
};



#endif
