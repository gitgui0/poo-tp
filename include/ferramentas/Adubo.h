#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"
#include <BocadoSolo.h>


class Adubo : public Ferramenta{
    public:
        Adubo();
        ~Adubo() override = default;

        bool aplica(BocadoSolo* b, Jardim* j) override;
        std::string mostra() const override;

        Ferramenta* clone() const override {return new Adubo(*this);}

    private:
        int capacidade;
};



#endif
