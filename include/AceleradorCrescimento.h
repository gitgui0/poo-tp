#ifndef TP_ACELERADORCRESCIMENTO_H
#define TP_ACELERADORCRESCIMENTO_H

#include "Ferramenta.h"


class AceleradorCrescimento : public Ferramenta {
public:
    AceleradorCrescimento();

    void aplica() override;
    std::string mostra() const override;

    ~AceleradorCrescimento() override;

private:
    int capacidade;
};


#endif //TP_ACELERADORCRESCIMENTO_H