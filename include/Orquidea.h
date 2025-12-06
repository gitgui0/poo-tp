
#ifndef TP_ORQUIDEA_H
#define TP_ORQUIDEA_H

#include "Planta.h"
#include <iostream>

class Orquidea : public Planta {
private:
    int instantesAguaAlta; //para contar quanto passou com a agua maior que 100

public:
    Orquidea();
    bool cadaInstante(BocadoSolo* b) override;
    void multiplica(BocadoSolo *b, Jardim* j) override;
    BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;
};




#endif //TP_ORQUIDEA_H