#include "Orquidea.h"
#include "Settings.h"
#include <iostream>
#include <vector>

Orquidea::Orquidea()
    : Planta(Settings::Orquidea::inicial_agua, Settings::Orquidea::inicial_nutrientes, 'x', "Bonita"),
      nInstantesAguaExcessiva(0)
{}

bool Orquidea::cadaInstante(BocadoSolo* b, Jardim* j) {
    countInstantes ++;

    bool estaFraca = false;

    if (b->getAgua() > Settings::Orquidea::agua_maior_perde && b->getAgua() < Settings::Orquidea::agua_menor_perde) {
        nInstantesAguaExcessiva++;
    } else {
        nInstantesAguaExcessiva = 0;
    }

    // se tiver fraca, ou seja, com muita agua durante mt tempo, tira nutrientes
    if (nInstantesAguaExcessiva >= Settings::Orquidea::agua_maior_instantes) {
        estaFraca = true;
    }

    b->setNutrientes(b->getNutrientes() - Settings::Orquidea::absorve_nutrientes);
    nutrientes += Settings::Orquidea::absorve_nutrientes;

    if (!estaFraca) {
        b->setAgua(b->getAgua() - Settings::Orquidea::absorve_agua);
        agua += Settings::Orquidea::absorve_agua;

        // retribuicao
        BocadoSolo* viz = geraVizinho(b,j);
        if (viz != nullptr) {
            viz->setNutrientes(viz->getNutrientes() + Settings::Orquidea::retribuicao_nutrientes);
        }

    }else {
        b->setAgua(b->getAgua() - Settings::Orquidea::absorve_agua_fraca);
        agua += Settings::Orquidea::absorve_agua_fraca;
    }


    return agua <= 0 || nutrientes <= 0;
}

void Orquidea::multiplica(BocadoSolo *b, Jardim* j) {
    if (nutrientes < Settings::Orquidea::multiplica_nutrientes_maior) return;

    BocadoSolo* vizinho = geraVizinho(b, j);

    if (vizinho != nullptr && vizinho->getAgua() > 40 && vizinho->getAgua() < 70) {
        Planta* p = new Orquidea();
        vizinho->setPlanta(p);
        nutrientes -= 25;
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
        if (viz && viz->getPlanta() == nullptr && viz->getAgua() > Settings::Orquidea::multiplica_agua_maior)
            escolhas.push_back(viz);
    }

    if (escolhas.empty()) return nullptr;
    return escolhas[rand() % escolhas.size()];
}