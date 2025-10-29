#include <iostream>
#include <sstream>
#include "Simulador.h"
#include "Comando.h"
#include "ComandoAvanca.h"

int main() {

    Simulador sim;

    ComandoAvanca ca;
    sim.adicionaComando(ca);

    std::string input;

    while (1) {
        std::cout << "\n>";
        std::getline(std::cin, input);

        if (input == "quit")
            break;

        if (!sim.executa(input))
            std::cout << "falhou" << std::endl;


    }

    return 0;
}