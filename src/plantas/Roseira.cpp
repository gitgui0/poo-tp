#include "Roseira.h"
#include "Settings.h"
#include <iostream>
#include <vector>

Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua,
                            Settings::Roseira::inicial_nutrientes,'r',"Bonita") {};

Roseira::Roseira(int agua, int nutrientes) : Planta(agua,nutrientes,'r',"Bonita") {};

void Roseira::multiplica(BocadoSolo *b, Jardim* j) {
    std::cout << "multiplica roseira" << std::endl;

    if (b == nullptr) return;

    if (nutrientes > Settings::Roseira::multiplica_nutrientes_maior) {

        BocadoSolo* vizinho = geraVizinho(b, j);

        if (vizinho != nullptr) {
            // criar novo
            int aguaFilha = agua * (Settings::Roseira::nova_agua_percentagem / 100.00);
            int nutriFilha = Settings::Roseira::nova_nutrientes;

            Planta* p = new Roseira(aguaFilha, nutriFilha);
            vizinho->setPlanta(p);

            agua = agua * (Settings::Roseira::original_agua_percentagem / 100.00);
            nutrientes = Settings::Roseira::original_nutrientes;
        }
    }
}

BocadoSolo* Roseira::geraVizinho(BocadoSolo *b, Jardim* j) const {
    if (b == nullptr) return nullptr;

    std::vector<BocadoSolo*> escolhas;
    std::pair<int, int> posicao = j->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    int dr[] = {-1, 1, 0, 0}; // Variacao na linha
    int dc[] = {0, 0, -1, 1}; // Variacao na coluna

    // Percorre as 4 direcoes
    for (int i = 0; i < 4; i++) {
        int nl = l + dr[i]; // Nova linha
        int nc = c + dc[i]; // Nova coluna

        if (nl >= 0 && nl < j->getLinhas() && nc >= 0 && nc < j->getColunas()) {

            BocadoSolo* vizinho = j->getBocado(nl, nc);

            if (vizinho->getPlanta() == nullptr)
                escolhas.push_back(vizinho);
        }
    }

    // nao ha vizinhos sem plantas
    if (escolhas.empty()) {
        return nullptr;
    }

    // gera um índice aleatório entre 0 e o tamanho do vetor
    int indiceSorteado = rand() % escolhas.size();

    return escolhas[indiceSorteado];
}


bool Roseira::cadaInstante(BocadoSolo* b, Jardim* j) {
    countInstantes ++;

    //usar o max aqui, previne valores negativos
    nutrientes = std::max(0,Settings::Roseira::perda_nutrientes);
    agua = std::max(0,Settings::Roseira::perda_nutrientes);

    // Esta logica esta assim porque "absorve 5 unidades de água do solo (se existir)", por causa do "se existir"
    int absorveNutri = ( b->getNutrientes() >= Settings::Roseira::absorcao_nutrientes ? Settings::Roseira::absorcao_nutrientes : 0);
    int absorveAgua = (b->getAgua() >= Settings::Roseira::absorcao_agua  ? Settings::Roseira::absorcao_agua  : 0);

    nutrientes += absorveNutri;
    agua += absorveAgua;

    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);

    // se a quantidade de água acumulada chegar a 0
    if (agua < Settings::Roseira::morre_agua_menor) {
        return true;
    }

    // se a quantidade de nutrientes acumulada chegar a 0
    if (nutrientes < Settings::Roseira::morre_nutrientes_menor) {
        return true;
    }

    //  se a quantidade de nutrientes acumulada atingir 200
    if (nutrientes > Settings::Roseira::morre_nutrientes_maior) {
        return true;
    }

    return geraVizinho(b,j) == nullptr; // se nao devolver nada, significa que nao ha posicoes livres, entao vai morrer
}


