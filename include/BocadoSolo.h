
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

      bool insere(Planta* item);
      bool remove(Planta* item);

      bool insere(Ferramenta* item);
      bool remove(Ferramenta* item);

      bool estaJardineiro() const noexcept;

      Planta* getPlanta() const noexcept { return planta; }
      Ferramenta* getFerramenta() const noexcept{ return ferramenta; }

      void colocaJardineiro();
      void removeJardineiro();

      char mostra();

    private:
      int agua;
      int nutrientes;

      bool ocupado;

      Planta *planta;
      Ferramenta* ferramenta;


};



#endif //BOCADOSOLO_H
