#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "EstaSolo.h"
#include "BocadoSolo.h"


class Planta : public EstaSolo {
    public:
        Planta(int agua, int nutrientes, char letra, const std::string& beleza);
        ~Planta() override = 0;

        std::string getBeleza() const { return beleza; }

        int obterAgua() const noexcept{ return agua; }
        int obterNutrientes() const noexcept{ return nutrientes; }
        int obterInstantes() const noexcept { return countInstantes; }

        virtual bool cadaInstante(BocadoSolo* b, Jardim* j) = 0;
        virtual void multiplica(BocadoSolo* b, Jardim* j) = 0;
        virtual BocadoSolo* geraVizinho(BocadoSolo* b, Jardim* j) const = 0;
        virtual Planta* clone() const = 0;

        static Planta* criar(char planta);

    protected:
        int agua;
        int nutrientes;
        int countInstantes;

        std::string beleza;
};


#endif