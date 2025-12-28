#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"
#include "Jardim.h"

class ErvaDaninha : public Planta{
    public:
        ErvaDaninha();
        ErvaDaninha(int agua, int nutrientes);
        ~ErvaDaninha() override = default;

        bool cadaInstante(BocadoSolo* b, Jardim* j) override;
        void multiplica(BocadoSolo *b, Jardim* j) override;
        BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;
        Planta* clone() const override {return new ErvaDaninha(*this);}

    private:
       int instanteMulti;

};



#endif
