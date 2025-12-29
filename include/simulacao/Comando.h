
#ifndef COMANDO_H
#define COMANDO_H

#include "Simulador.h"

class Comando {
    public:
        Comando() = default;
        virtual ~Comando() = default;
        virtual void executa(Simulador &sim, std::istringstream & params) const = 0;
        virtual string getNome() = 0;

};



#endif
