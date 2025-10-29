#include <iostream>
#include <sstream>
#include "Simulador.h"
#include "Comando.h"
#include "ComandoAvanca.h"
#include "Interface.h"

int main() {

    Simulador sim;


    std::string input;

    Interface ui(&sim);
    ui.inicia();

    return 0;
}