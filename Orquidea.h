
#ifndef TP_ORQUIDEA_H
#define TP_ORQUIDEA_H

#include "Planta.h"

class Orquidea : public Planta {
private:
    int instantesAguaAlta; //para contar quanto passou com a agua maior que 100

public:
    Orquidea();
    void cadaInstante() override; //o que faz a cada instante
};




#endif //TP_ORQUIDEA_H