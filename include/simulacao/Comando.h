
#ifndef COMANDO_H
#define COMANDO_H

#include <sstream>
#include "Simulador.h"


class Comando {
    public:
        Comando() = default;
        ~Comando() = default;
        virtual void executa(Simulador &sim, std::istringstream & params) const = 0;
        virtual const string getNome() = 0;

};



#endif
