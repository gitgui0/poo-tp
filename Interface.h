
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
        ~Interface();
        void inicia(); // loop principal
        void mostraJardim() const;

};


#endif //TP_INTERFACE_H