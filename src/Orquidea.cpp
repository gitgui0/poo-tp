#include "Orquidea.h"
#include "Settings.h"
#include "Planta.h"
#include <iostream>
#include <vector>

Orquidea::Orquidea()
    :Planta(Settings::Orquidea::inicial_agua,
        Settings::Orquidea::inicial_nutrientes,
        'x',
        "Bonita"), instantesAguaAlta(0){}

void Orquidea::multiplica(BocadoSolo *b, Jardim* j) {
    // [Mantido] Log do teu colega
    std::cout << "multiplica orquidea" << std::endl;

    if (b == nullptr) return;

    // Usa os valores definidos no Settings.h para a Orquidea
    // Exige: Nutrientes > 60 E Agua > 80 (valores do teu Settings)
    if (obterNutrientes() > Settings::Orquidea::multiplica_nutrientes_maior &&
        obterAgua() > Settings::Orquidea::multiplica_agua_maior) {

        // A Orquidea usa o geraVizinho padrão (que só devolve vazios, verifiquei no código anterior)
        BocadoSolo* vizinho = geraVizinho(b, j);

        if (vizinho != nullptr) {
            // Estratégia de Divisão Justa
            int aguaPassada = obterAgua() / 2;
            int nutriPassado = obterNutrientes() / 2;

            // Criar a nova Orquidea.
            // Como o construtor da Orquidea não recebe argumentos (usa defaults),
            // criamos e depois ajustamos os valores.
            Orquidea* p = new Orquidea();
            p->colocarAgua(aguaPassada);
            p->colocarNutrientes(nutriPassado);

            vizinho->setPlanta(p);

            // Atualiza a MÃE
            colocarAgua(aguaPassada);
            colocarNutrientes(nutriPassado);
        }
        }
}

BocadoSolo* Orquidea::geraVizinho(BocadoSolo *b, Jardim* j) const {
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


void Orquidea::cadaInstante(BocadoSolo* b) {
    int absorveNutri = ( b->getNutrientes() >= 4 ? 4 : 0);
    int absorveAgua = (b->getAgua() >= 3 ? 3 : 0);

    colocarNutrientes(obterNutrientes() + absorveNutri);
    colocarAgua(obterAgua() + absorveAgua);

    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);
}

