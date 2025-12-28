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

    //perde agua e nutrientes

    agua -= 2;
    nutrientes -= 1;

    bool estaFraca = false;

    if (b->getAgua() > 80 && b->getAgua() < 30) {
        nInstantesAguaExcessiva++;
    } else {
        nInstantesAguaExcessiva = 0;
    }

    // se tiver fraca, ou seja, com muita agua durante mt tempo, tira nutrientes
    if (nInstantesAguaExcessiva >= 2) {
        estaFraca = true;
        nutrientes -= 10;
    }

    // bebe 10
    if (b->getAgua() >= 10) {
        b->setAgua(b->getAgua() - 10);
        agua += 10;

        // se nao estiver fraca, retribui com 5 nutrientes e absorve nutrientes tambem
        if (!estaFraca) {
            b->setNutrientes(b->getNutrientes() + 5);
            nutrientes += 2;
        }
    } else {
        // se nao havia 10 aguas no solo, perde mais agua e tira nutrientes do solo
        b->setAgua(b->getAgua() - 5);
        agua -= 5;
        b->setNutrientes(b->getNutrientes() - 5);
        nutrientes -= 5;
    }

    if (agua <= 0 || nutrientes <= 0) {
        return true;
    }

    return false;
}

void Orquidea::multiplica(BocadoSolo *b, Jardim* j) {
    if (nutrientes < 50) return;

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
        if (viz && viz->getPlanta() == nullptr) escolhas.push_back(viz);
    }

    if (escolhas.empty()) return nullptr;
    return escolhas[rand() % escolhas.size()];
}