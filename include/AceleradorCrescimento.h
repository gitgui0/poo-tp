#ifndef TP_ACELERADORCRESCIMENTO_H
#define TP_ACELERADORCRESCIMENTO_H

#include <BocadoSolo.h>

#include "Ferramenta.h"


class AceleradorCrescimento : public Ferramenta {
public:
    AceleradorCrescimento();

    bool aplica(BocadoSolo* b, Jardim* j) override;
    std::string mostra() const override;

    Ferramenta* clone() const{return new AceleradorCrescimento(*this);}

    ~AceleradorCrescimento() override;

private:
    int capacidade;
};


#endif //TP_ACELERADORCRESCIMENTO_H