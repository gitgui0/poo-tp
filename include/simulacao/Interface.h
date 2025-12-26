
#ifndef TP_INTERFACE_H
#define TP_INTERFACE_H

#include <string>

using namespace std;
class Simulador;

class Interface {
    Simulador* sim;
    bool ligado;

    public:
        explicit Interface(Simulador * sim);
        ~Interface() = default;
        void inicia(); // loop principal
        void setLigado(bool l){ligado = l;}

};


#endif //TP_INTERFACE_H