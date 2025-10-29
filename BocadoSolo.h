
#ifndef BOCADOSOLO_H
#define BOCADOSOLO_H

#include "EstaSolo.h"

#include <string>

class BocadoSolo {
    public:
      BocadoSolo();

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

      EstaSolo *objetos[2];  // [2] para planta e ferramenta


};



#endif //BOCADOSOLO_H
