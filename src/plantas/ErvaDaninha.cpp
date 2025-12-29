#include "ErvaDaninha.h"
#include "Settings.h"

#include <iostream>
#include <vector>

ErvaDaninha::ErvaDaninha() :
    Planta(Settings::ErvaDaninha::inicial_agua,Settings::ErvaDaninha::inicial_nutrientes,
        'e',"Feia"), instanteMulti(0)
{}

ErvaDaninha::ErvaDaninha(int agua, int nutrientes) :
    Planta(agua,nutrientes,
        'e',"Feia"), instanteMulti(0)
{}


void ErvaDaninha::multiplica(BocadoSolo *b, Jardim* j) {

    if (b == nullptr) return;

    // Regra: Nutrientes > 30 (Settings::ErvaDaninha::multiplica_nutrientes_maior) e se os inatntes desde a ultia multiplicaco > 5
    if (nutrientes > Settings::ErvaDaninha::multiplica_nutrientes_maior && countInstantes - instanteMulti >= Settings::ErvaDaninha::multiplica_instantes) {
        instanteMulti = countInstantes;

        // O geraVizinho da ErvaDaninha (já implementado) devolve QUALQUER vizinho.
        BocadoSolo* vizinho = geraVizinho(b, j);

        if (vizinho != nullptr) {
            // A original fica igual (não perde recursos, segundo o enunciado)
            // A nova "Fica com 5 de água, e 5 de nutrientes"

            int aguaFilha = Settings::ErvaDaninha::inicial_agua;
            int nutriFilha = Settings::ErvaDaninha::nova_nutrientes;

            // Ao fazer setPlanta, se já lá estiver uma planta, o BocadoSolo
            // encarrega-se de fazer 'delete' da anterior (matando-a).
            Planta* p = new ErvaDaninha(aguaFilha, nutriFilha);
            vizinho->setPlanta(p);

            //std::cout << "Erva daninha multiplicou-se" << std::endl;
        }
    }
}



BocadoSolo* ErvaDaninha::geraVizinho(BocadoSolo *b, Jardim* j) const {
    if (b == nullptr) return nullptr;

    std::vector<BocadoSolo*> escolhas;
    std::pair<int, int> posicao = j->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    int dr[] = {-1, 1, 0, 0}; // Variacao na linha
    int dc[] = {0, 0, -1, 1}; // Variacao na coluna

    // Percorre as 4 direcoes possíveis
    for (int i = 0; i < 4; i++) {
        int nl = l + dr[i]; // Nova linha
        int nc = c + dc[i]; // Nova coluna

        if (nl >= 0 && nl < j->getLinhas() && nc >= 0 && nc < j->getColunas()) {

            BocadoSolo* vizinho = j->getBocado(nl, nc);

            //para a erva daninha, nao interessa se tem planta ou nao
            escolhas.push_back(vizinho);

        }
    }


    if (escolhas.empty()) {
        return nullptr; // Não há vizinhos válidos
    }

    int indiceSorteado = rand() % escolhas.size();

    return escolhas[indiceSorteado];
}


bool ErvaDaninha::cadaInstante(BocadoSolo* b, Jardim* j) {
    countInstantes++;

    int absorveNutri = std::min((int)Settings::ErvaDaninha::absorcao_nutrientes,b->getNutrientes());
    int absorveAgua = std::min((int)Settings::ErvaDaninha::absorcao_agua, b->getAgua());


    if (b->setNutrientes(b->getNutrientes() - absorveNutri))
        nutrientes += absorveNutri;
    if (b->setAgua(b->getAgua() - absorveAgua))
        agua += absorveAgua;

    return countInstantes >= Settings::ErvaDaninha::morre_instantes;
}