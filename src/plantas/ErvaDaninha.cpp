#include "ErvaDaninha.h"
#include "Settings.h"

#include <iostream>
#include <vector>

ErvaDaninha::ErvaDaninha() :
    Planta(Settings::ErvaDaninha::inicial_agua,Settings::ErvaDaninha::inicial_nutrientes,
        'e',"Feia"), instanteMulti(0)
{};

ErvaDaninha::ErvaDaninha(int agua, int nutrientes) :
    Planta(agua,nutrientes,
        'e',"Feia"), instanteMulti(0)
{};

ErvaDaninha::~ErvaDaninha(){ std::cout << "Destructor Erva Daninha" << std::endl;}

void ErvaDaninha::multiplica(BocadoSolo *b, Jardim* j) {
    // [Mantido] Log do teu colega
    std::cout << "multiplica erva daninha" << std::endl;

    if (b == nullptr) return;

    // Regra: Nutrientes > 30 (Settings::ErvaDaninha::multiplica_nutrientes_maior) e se os inatntes desde a ultia multiplicaco > 5
    if (obterNutrientes() > Settings::ErvaDaninha::multiplica_nutrientes_maior && obterInstantes() - instanteMulti >= Settings::ErvaDaninha::multiplica_instantes) {
        instanteMulti = obterInstantes();

        // O geraVizinho da ErvaDaninha (já implementado) devolve QUALQUER vizinho.
        BocadoSolo* vizinho = geraVizinho(b, j);

        if (vizinho != nullptr) {
            // Criar a FILHA (invasora)
            // "Fica com 5 de água, e 5 de nutrientes"
            int aguaFilha = Settings::ErvaDaninha::inicial_agua;      // 5
            int nutriFilha = Settings::ErvaDaninha::nova_nutrientes;  // 5

            // Ao fazer setPlanta, se já lá estiver uma planta, o BocadoSolo
            // encarrega-se de fazer 'delete' da anterior (matando-a).
            Planta* p = new ErvaDaninha(aguaFilha, nutriFilha);
            vizinho->setPlanta(p);

            // A MÃE mantém-se igual (não perde recursos, segundo o enunciado)
        }
    }
}



BocadoSolo* ErvaDaninha::geraVizinho(BocadoSolo *b, Jardim* j) const {
    if (b == nullptr) return nullptr;

    std::vector<BocadoSolo*> escolhas;
    std::pair<int, int> posicao = j->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    // Arrays auxiliares para as 4 direções (Cima, Baixo, Esquerda, Direita)
    int dr[] = {-1, 1, 0, 0}; // Variacao na linha
    int dc[] = {0, 0, -1, 1}; // Variacao na coluna

    // Percorre as 4 direções possíveis
    for (int i = 0; i < 4; i++) {
        int nl = l + dr[i]; // Nova linha
        int nc = c + dc[i]; // Nova coluna

        if (nl >= 0 && nl < j->getLinhas() && nc >= 0 && nc < j->getColunas()) {

            BocadoSolo* vizinho = j->getBocado(nl, nc);

            //nao interessa se tem planta ou nao
            escolhas.push_back(vizinho);

        }
    }

    // 3. Escolha Aleatória
    if (escolhas.empty()) {
        return nullptr; // Não há vizinhos válidos (ou vazios)
    }

    // Gera um índice aleatório entre 0 e o tamanho do vetor - 1
    int indiceSorteado = rand() % escolhas.size();

    return escolhas[indiceSorteado];
}


bool ErvaDaninha::cadaInstante(BocadoSolo* b, Jardim* j) {
    aumentaInstantes();

    int absorveNutri = ( b->getNutrientes() > 0 ? Settings::ErvaDaninha::absorcao_nutrientes : 0);
    int absorveAgua = (b->getAgua() > 0 ? Settings::ErvaDaninha::absorcao_agua : 0);

    colocarNutrientes(obterNutrientes() + absorveNutri);
    colocarAgua(obterAgua() + absorveAgua);

    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);

    return obterNutrientes() >= Settings::ErvaDaninha::morre_instantes;
}