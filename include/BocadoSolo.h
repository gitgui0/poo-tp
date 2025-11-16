
#ifndef BOCADOSOLO_H
#define BOCADOSOLO_H

#include "Planta.h"
#include "Ferramenta.h"

#include <string>

class BocadoSolo {
    public:
      BocadoSolo();
     ~BocadoSolo();

      int getAgua() const noexcept;
      int getNutrientes() const noexcept;

      bool setAgua(int agua);
      bool setNutrientes(int nutrientes);

      bool insere(EstaSolo* item);
      bool remove(EstaSolo* item);

      bool estaJardineiro() const noexcept;

      void colocaJardineiro();
      void removeJardineiro();

        std::string mostra();

    private:
      int agua;
      int nutrientes;

      bool ocupado;

      Planta* planta;
      Ferramenta* ferramenta;


};



#endif //BOCADOSOLO_H
