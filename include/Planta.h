#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "EstaSolo.h"

class Planta : public EstaSolo {
    public:
      void obterAgua(int agua);
      void obterNutrientes(int nutrientes);

      void colocarAgua(int agua);
      void colocarNutrientes(int nutrientes);

      virtual void cadaInstante() = 0;

      //TODO: funcao para multiplicar, provavelmente virtual também

      ~Planta() override = 0; // override do destrutor do estasolo

      Planta(int agua, int nutrientes, char letra, const std::string& beleza);

      //TODO: copy constructor, nao sabemos ainda se vai ser necessário


    private:
      int agua;
      int nutrientes;
      int countInstantes;

      std::string beleza;
};


#endif