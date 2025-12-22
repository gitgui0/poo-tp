#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "EstaSolo.h"
#include "BocadoSolo.h"
#include "Jardim.h"

class Planta : public EstaSolo {
    public:
      int obterAgua() const noexcept{ return agua; }
      int obterNutrientes() const noexcept{ return nutrientes; }

      void colocarAgua(int agua);
      void colocarNutrientes(int nutrientes);

      virtual bool cadaInstante(BocadoSolo* b, Jardim* j) = 0;

      virtual void multiplica(BocadoSolo* b, Jardim* j) = 0;

      virtual BocadoSolo* geraVizinho(BocadoSolo* b, Jardim* j) const = 0;

      std::string getBeleza() const { return beleza; }

      ~Planta() override = 0; // override do destrutor do estasolo

      Planta(int agua, int nutrientes, char letra, const std::string& beleza);

      virtual Planta* clone() const = 0;


    private:
      int agua;
      int nutrientes;
      int countInstantes;

      std::string beleza;
};


#endif