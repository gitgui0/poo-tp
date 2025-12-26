#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"
#include "Jardim.h"

class Cacto : public Planta {
    public:
        Cacto();
        Cacto(int agua, int nutri );
        ~Cacto() override = default;

        bool cadaInstante(BocadoSolo* b, Jardim* j) override;
        void multiplica(BocadoSolo *b, Jardim* j) override;
        BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;
        Planta* clone() const override {return new Cacto(*this);}

    private:
        int turnosAguaExcessiva;
        int turnosNutrientesExcessivos;

};



#endif
