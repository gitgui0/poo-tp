#ifndef TP_ACELERADORCRESCIMENTO_H
#define TP_ACELERADORCRESCIMENTO_H

#include <BocadoSolo.h>
#include "Ferramenta.h"


class AceleradorCrescimento : public Ferramenta {
    public:
        AceleradorCrescimento();
        ~AceleradorCrescimento() override = default;

        bool aplica(BocadoSolo* b, Jardim* j) override;
        std::string mostra() const override;

        Ferramenta* clone() const override{return new AceleradorCrescimento(*this);}

    private:
        int capacidade;
};


#endif