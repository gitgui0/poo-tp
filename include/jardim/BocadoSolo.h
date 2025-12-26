
#ifndef BOCADOSOLO_H
#define BOCADOSOLO_H

#include "Ferramenta.h"

class Planta;

class BocadoSolo {
    public:
        BocadoSolo();
        BocadoSolo(const BocadoSolo& outro);
        ~BocadoSolo();

        BocadoSolo& operator=(const BocadoSolo& outro);

        // Devolve a ferramenta mas nao liberta a memoria, apenas retira do solo
        Ferramenta* retiraFerramenta();

        Planta* getPlanta() const noexcept { return planta; }
        Ferramenta* getFerramenta() const noexcept{ return ferramenta; }

        void setPlanta(Planta* p);
        void setFerramenta(Ferramenta* f);

        int getAgua() const noexcept { return agua;}
        int getNutrientes() const noexcept { return nutrientes;}

        bool setAgua(int agua);
        bool setNutrientes(int nutrientes);

        bool estaJardineiro() const noexcept { return ocupado; }
        void removeJardineiro() {ocupado = false;}
        void colocaJardineiro() {ocupado = true;}

        char mostra();

    private:
        int agua;
        int nutrientes;

        bool ocupado;

        Planta *planta;
        Ferramenta* ferramenta;

};



#endif
