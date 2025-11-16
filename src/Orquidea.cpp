#include "Orquidea.h"
#include "Settings.h"
#include "Planta.h"
#include <iostream>

Orquidea::Orquidea()
    :Planta(Settings::Orquidea::inicial_agua,
        Settings::Orquidea::inicial_nutrientes,
        'x',
        "Bonita"), instantesAguaAlta(0){}

void Orquidea::cadaInstante() {
    obterAgua(Settings::Orquidea::absorve_agua);
    obterNutrientes(Settings::Orquidea::absorve_nutrientes);

    //para completar depois
    std::cout << "Orquidea executou um instante" << std::endl;

}
