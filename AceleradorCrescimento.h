#ifndef TP_ACELERADORCRESCIMENTO_H
#define TP_ACELERADORCRESCIMENTO_H

#include "Ferramenta.h"
#include <iostream>

class AceleradorCrescimento : public Ferramenta {
public:
    AceleradorCrescimento();

    void aplica() override;

    ~AceleradorCrescimento() override;

private:
    int capacidade;
};


#endif //TP_ACELERADORCRESCIMENTO_H