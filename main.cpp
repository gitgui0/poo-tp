
#include "Simulador.h"


int main() {
    Simulador sim;
    Interface* ui = sim.devolveInterface();

    ui->inicia();

    return 0;
}