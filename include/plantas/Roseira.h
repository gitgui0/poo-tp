#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"
#include "Jardim.h"

class Roseira : public Planta{

    public:
        Roseira();
        Roseira(int agua, int nutrientes);
        ~Roseira() override = default;

        bool cadaInstante(BocadoSolo* b, Jardim* j) override;
        void multiplica(BocadoSolo *b, Jardim* j) override;
        BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;

        Planta* clone() const override {return new Roseira(*this);}
};



#endif
