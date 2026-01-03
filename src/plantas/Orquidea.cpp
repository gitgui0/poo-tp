#include "Orquidea.h"
#include "SettingsExtra.h"
#include <iostream>
#include <vector>

Orquidea::Orquidea()
    : Planta(SettingsExtra::Orquidea::inicial_agua, SettingsExtra::Orquidea::inicial_nutrientes, 'x', "Bonita"),
      nInstantesAguaExcessiva(0)
{}

bool Orquidea::cadaInstante(BocadoSolo* b, Jardim* j) {
    countInstantes ++;

    bool estaFraca = false;

    if (b->getAgua() > SettingsExtra::Orquidea::agua_maior_perde || b->getAgua() < SettingsExtra::Orquidea::agua_menor_perde) {
        nInstantesAguaExcessiva++;
    } else {
        nInstantesAguaExcessiva = 0;
    }

    // se tiver fraca, ou seja, com muita agua durante mt tempo, tira nutrientes
    if (nInstantesAguaExcessiva >= SettingsExtra::Orquidea::agua_prejudicial_instantes) {
        estaFraca = true;
    }

    int absorveNutri = std::min((int)SettingsExtra::Orquidea::absorve_nutrientes, b->getNutrientes());


    if (b->setNutrientes(b->getNutrientes() - absorveNutri))
        nutrientes += absorveNutri;

    if (!estaFraca) {
        int absorveAgua = std::min((int)SettingsExtra::Orquidea::absorve_agua, b->getAgua());

        if (b->setAgua(b->getAgua() - absorveAgua))
            agua += absorveAgua;

        // Retribuicao
        BocadoSolo* viz = geraVizinho(b,j);
        if (viz != nullptr) {
            int ret = std::min(nutrientes, (int)SettingsExtra::Orquidea::retribuicao_nutrientes);
            viz->setNutrientes(viz->getNutrientes() + ret);
            nutrientes -= ret;
        }

    }else {
        int absorveAgua = std::min((int)SettingsExtra::Orquidea::absorve_agua_fraca, b->getAgua());
        if (agua < SettingsExtra::Orquidea::agua_menor_perde && b->setAgua(b->getAgua() - absorveAgua))
            agua += absorveAgua;
    }


    return nInstantesAguaExcessiva >= SettingsExtra::Orquidea::instantes_morre;
}

void Orquidea::multiplica(BocadoSolo *b, Jardim* j) {
    if (nutrientes < SettingsExtra::Orquidea::multiplica_nutrientes_maior) return;

    BocadoSolo* vizinho = geraVizinho(b, j);

    if (vizinho != nullptr && vizinho->getAgua() > SettingsExtra::Orquidea::multiplica_agua_maior) {
        Planta* p = new Orquidea();
        vizinho->setPlanta(p);
        nutrientes = std::max(0,nutrientes - SettingsExtra::Orquidea::inicial_nutrientes);
        //std::cout << "A Orquidea multiplicou-se" << std::endl;
    }
}

BocadoSolo* Orquidea::geraVizinho(BocadoSolo *b, Jardim* j) const {
    if (b == nullptr) return nullptr;
    std::vector<BocadoSolo*> escolhas;
    std::pair<int, int> pos = j->getPosicaoBocado(b);
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        BocadoSolo* viz = j->getBocado(pos.first + dr[i], pos.second + dc[i]);
        if (viz && viz->getPlanta() == nullptr && viz->getAgua() > SettingsExtra::Orquidea::multiplica_agua_maior)
            escolhas.push_back(viz);
    }

    if (escolhas.empty()) return nullptr;
    return escolhas[rand() % escolhas.size()];
}