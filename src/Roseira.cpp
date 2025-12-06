#include "Roseira.h"
#include "Settings.h"
#include <iostream>
#include <vector>

Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua,
                            Settings::Roseira::inicial_nutrientes,'r',"Bonita") {};
Roseira::~Roseira(){ std::cout << "Desconstrutor roseira " << std::endl;}


void Roseira::multiplica(BocadoSolo *b, Jardim* j) {
    // [Mantido] Log do teu colega
    std::cout << "multiplica roseira" << std::endl;

    if (b == nullptr) return;

    // Regra: Nutrientes > 100 (Settings::Roseira::multiplica_nutrientes_maior)
    if (obterNutrientes() > Settings::Roseira::multiplica_nutrientes_maior) {

        // O geraVizinho da Roseira (já implementado) só devolve vizinhos VAZIOS.
        BocadoSolo* vizinho = geraVizinho(b, j);

        if (vizinho != nullptr) {
            // Criar a FILHA
            // "Começa com 25 nutrientes e metade da água"
            int aguaFilha = obterAgua() / 2;
            int nutriFilha = Settings::Roseira::nova_nutrientes; // 25

            // Nota: O construtor recebe (agua, nutrientes)
            Planta* p = new Roseira(aguaFilha, nutriFilha);
            vizinho->setPlanta(p);

            // Atualizar a MÃE
            // "Fica com 100 unidades de nutrientes e com metade da água"
            colocarAgua(obterAgua() / 2); // Perde metade da agua
            colocarNutrientes(100);       // Reset aos nutrientes para 100
        }
    }
}



BocadoSolo* Roseira::geraVizinho(BocadoSolo *b, Jardim* j) const {
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

            if (vizinho->getPlanta() == nullptr)
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


void Roseira::cadaInstante(BocadoSolo* b) {
    colocarNutrientes(obterNutrientes() - 4);
    colocarAgua(obterAgua() - 4);

    int absorveNutri = ( b->getNutrientes() >= 5 ? 5 : 0);
    int absorveAgua = (b->getAgua() >= 8 ? 8 : 0);

    colocarNutrientes(obterNutrientes() + absorveNutri);
    colocarAgua(obterAgua() + absorveAgua);

    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);
}
