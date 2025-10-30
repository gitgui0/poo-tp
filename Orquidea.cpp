#include "Orquidea.h"
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

    //umas validacoes assim
    //ver se a agua ta acima de 100
    if (Settings::Orquidea::agua_maior_perde > 0) {
        if (/*se existir um "getAgua()"*/ false) {
            //quando tiver essa funcao
        }
    }
    //para completar depois
    std::cout << "Orquidea executou um instante" << std::endl;

    //para quando usares no simulador
    /*#include "Orquidea.h"
    Planta* p = new Orquidea();*/

}
