#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"
#include <iostream>

class Cacto : public Planta {
    public:
      bool cadaInstante(BocadoSolo* b) override;
      void multiplica(BocadoSolo *b, Jardim* j) override;
      BocadoSolo* geraVizinho(BocadoSolo *b, Jardim* j) const override;

      Planta* clone() const override {return new Cacto(*this);}

      Cacto();
      Cacto(int agua, int nutri );
      ~Cacto() override;

    private:
        int turnosAguaExcessiva;
        int turnosNutrientesExcessivos;

};



#endif
