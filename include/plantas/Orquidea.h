
#ifndef TP_ORQUIDEA_H
#define TP_ORQUIDEA_H

#include "Planta.h"
#include "Jardim.h"

class Orquidea : public Planta {

    public:
        Orquidea();
        ~Orquidea() override = default;

        bool cadaInstante(BocadoSolo* b, Jardim* j) override;
        void multiplica(BocadoSolo *b, Jardim* j) override;
        BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;
        Planta* clone() const override {return new Orquidea(*this);}

    private:
        int nInstantesAguaExcessiva;
};




#endif //TP_ORQUIDEA_H