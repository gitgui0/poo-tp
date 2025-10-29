
#ifndef TP_INTERFACE_H
#define TP_INTERFACE_H

#include <string>
#include <iostream>

#include "Simulador.h"

using namespace std;

class Interface {
    bool running;
    Simulador* sim;

    public:
        explicit Interface(Simulador * sim);
        ~Interface();
        void inicia(); // loop principal
        void mostraJardim() const;

};


#endif //TP_INTERFACE_H