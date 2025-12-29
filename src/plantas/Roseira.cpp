#include "Roseira.h"
#include "Settings.h"
#include <iostream>
#include <vector>

Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua,
                            Settings::Roseira::inicial_nutrientes,'r',"Bonita") {}

Roseira::Roseira(const int agua, const int nutrientes) : Planta(agua,nutrientes,'r',"Bonita") {}

void Roseira::multiplica(BocadoSolo *b, Jardim* j) {


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

            //std::cout << "A Roseira multiplicou-se" << std::endl;
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

    int indiceSorteado = rand() % escolhas.size();

    return escolhas[indiceSorteado];
}


bool Roseira::cadaInstante(BocadoSolo* b, Jardim* j) {
    countInstantes ++;

    //usar o max aqui, previne valores negativos
    nutrientes = std::max(0, nutrientes - (int)Settings::Roseira::perda_nutrientes);
    agua = std::max(0, agua - (int)Settings::Roseira::perda_agua);

    int absorveNutri = std::min((int)Settings::Roseira::absorcao_nutrientes, b->getNutrientes());
    int absorveAgua = std::min((int)Settings::Roseira::absorcao_agua, b->getAgua());

    if (b->setNutrientes(b->getNutrientes() - absorveNutri))
        nutrientes += absorveNutri;
    if (b->setAgua(b->getAgua() - absorveAgua))
        agua += absorveAgua;


    bool vaiMorrer = false;
    if (agua < Settings::Roseira::morre_agua_menor)
        vaiMorrer = true;

    if (nutrientes < Settings::Roseira::morre_nutrientes_menor)
        vaiMorrer = true;

    if (nutrientes > Settings::Roseira::morre_nutrientes_maior)
        vaiMorrer = true;

    // se nao devolver nada, significa que nao ha posicoes livres, entao vai morrer
    if (geraVizinho(b,j) == nullptr)
        vaiMorrer = true;

    if (vaiMorrer) {
        // Ao morrer deixa no solo metade dos nutrientes e metade da agua
        b->setNutrientes(b->getNutrientes() + (this->nutrientes / 2));
        b->setAgua(b->getAgua() + (this->agua / 2));
    }

    return vaiMorrer;
}


