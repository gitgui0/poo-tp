#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "EstaSolo.h"

class Planta : EstaSolo {
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


      // Se countInstantes for private, funcao getInstante

    private:
      int agua;
      int nutrientes;
      int countInstantes; // private?, herda para todas?

      std::string beleza;
};


#endif