#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"
#include <iostream>

class Roseira : public Planta{
    public:
        bool cadaInstante(BocadoSolo* b) override;
        void multiplica(BocadoSolo *b, Jardim* j) override;
        BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;

        Roseira();
        Roseira(int agua, int nutrientes);
        ~Roseira();
};



#endif
