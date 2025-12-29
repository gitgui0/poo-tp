
#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"


class Regador : public Ferramenta{
    public:
        Regador();
        ~Regador() override = default;

        bool aplica(BocadoSolo* b, Jardim* j) override;
        std::string mostra() const override;
        Ferramenta* clone() const override {return new Regador(*this);}

    private:
      int capacidade;

};

#endif
