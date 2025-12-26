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

    if (obterNutrientes() > Settings::Roseira::multiplica_nutrientes_maior) {

        BocadoSolo* vizinho = geraVizinho(b, j);

        if (vizinho != nullptr) {
            // criar novo
            int aguaFilha = obterAgua() / 2;
            int nutriFilha = Settings::Roseira::nova_nutrientes;

            Planta* p = new Roseira(aguaFilha, nutriFilha);
            vizinho->setPlanta(p);

            colocarAgua(obterAgua() / 2); // perde metade da agua
            colocarNutrientes(100); // nutrientes volta a 100
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
    aumentaInstantes();
    colocarNutrientes(obterNutrientes() - 4);
    colocarAgua(obterAgua() - 4);

    int absorveNutri = ( b->getNutrientes() >= 5 ? 5 : 0);
    int absorveAgua = (b->getAgua() >= 8 ? 8 : 0);

    colocarNutrientes(obterNutrientes() + absorveNutri);
    colocarAgua(obterAgua() + absorveAgua);

    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);

    // se a quantidade de água acumulada chegar a 0
    if (obterAgua() < Settings::Roseira::morre_agua_menor) {
        return true;
    }

    // se a quantidade de nutrientes acumulada chegar a 0
    if (obterNutrientes() < Settings::Roseira::morre_nutrientes_menor) {
        return true;
    }

    //  se a quantidade de nutrientes acumulada atingir 200
    if (obterNutrientes() > Settings::Roseira::morre_nutrientes_maior) {
        return true;
    }

    return geraVizinho(b,j) == nullptr; // se nao devolver nada, significa que nao ha posicoes livres, entao vai morrer
}


