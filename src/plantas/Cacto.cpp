#include "Cacto.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "Settings.h"

Cacto::Cacto() : Planta(0,0,'c',"Neutra"), turnosAguaExcessiva(0), turnosNutrientesExcessivos(0) {};
Cacto::Cacto(int agua, int nutrientes) : Planta(agua,nutrientes,'c',"Neutra"), turnosAguaExcessiva(0), turnosNutrientesExcessivos(0){};

bool Cacto::cadaInstante(BocadoSolo* b, Jardim* j) {
    countInstantes ++;

    if (b->getAgua() > Settings::Cacto::absorcao_agua_percentagem)
        turnosAguaExcessiva++;
    else
        turnosAguaExcessiva=0;

    if (b->getNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor)
        turnosNutrientesExcessivos++;
    else
        turnosNutrientesExcessivos=0;

    int absorveNutri = std::min(Settings::Cacto::absorcao_nutrientes,b->getNutrientes());
    // se a agua no solo for 0, fica absorve 0, se estiver entre 1 e 4, absorve 1
    int absorveAgua = std::ceil(b->getAgua() * (double)Settings::Cacto::absorcao_agua_percentagem /100);

    //Colocar a agua e nutrientes na planta. atuais + absorvidos
    nutrientes += absorveNutri;
    agua += absorveAgua;

    //Colocar a agua e nutrientes no bocado de solo (b). atuais - absorvidos
    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);

    return
        turnosAguaExcessiva >= Settings::Cacto::morre_agua_solo_instantes
        || turnosNutrientesExcessivos >= Settings::Cacto::morre_nutrientes_solo_menor
    ;
}

void Cacto::multiplica(BocadoSolo *b, Jardim* j) {
    if (b==nullptr)
        throw std::runtime_error("Erro inesperado. Esse solo nao existe");

    //Condicoes para multiplicar (neste caso e nele proprio, mas em outras plantas, a condicao
    // teria que estar ser verificada na posicao vizinha, ou seja, na funcao geraVizinho )
    if (!( nutrientes > Settings::Cacto::multiplica_nutrientes_maior && agua > Settings::Cacto::morre_nutrientes_solo_menor ))
        return;

    BocadoSolo* vizinho = geraVizinho(b,j);
    if (vizinho==nullptr)
        return;

    //Criar um cacto com os nutrientes e agua do cacto "pai"
    Planta* p  = new Cacto(agua / 2,nutrientes / 2);

    // Atualizar a gua e nutrienttes do cacto "pai"
    agua = agua / 2;
    nutrientes = nutrientes / 2;

    // Colocar no vizinho o cacto novo
    vizinho->setPlanta(p);
}

// Funcao para gerar vizinhos de uma certa posicao, varia de planta para planta, porque ha plantas que
// se multiplicam em condicoes diferentes, o viznhio tem que ter x de agua e y de nutrientes por exemplo.
// Ha plantas que essas condicoes nem se verificam nesta funcao. É ler o enunciado.
BocadoSolo* Cacto::geraVizinho(BocadoSolo *b, Jardim* j) const {
    if (b == nullptr) return nullptr;

    std::vector<BocadoSolo*> escolhas;
    //posicao do proprio bocado solo
    std::pair<int, int> posicao = j->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    // arrays auxiliares para as 4 direcoes (cima, baixo, esquerda, direita)
    int dr[] = {-1, 1, 0, 0}; // Variacao na linha, esquerda(-1)  / direita (1)
    int dc[] = {0, 0, -1, 1}; // Variacao na coluna, baixo(-1) / cima(1)

    // Percorre as 4 direções possíveis
    for (int i = 0; i < 4; i++) {
        int nl = l + dr[i]; // Nova linha
        int nc = c + dc[i]; // Nova coluna

        if (nl >= 0 && nl < j->getLinhas() && nc >= 0 && nc < j->getColunas()) {

            BocadoSolo* vizinho = j->getBocado(nl, nc);

            // Na erva daninha, esta condicao nao e necessaria, visto que a erva daninha pode so multiplicar mesmo
            // que exista la uma planta ou nao
            if (vizinho->getPlanta() == nullptr)
                { escolhas.push_back(vizinho); }
        }
    }

    // Não há vizinhos validos
    if (escolhas.empty()) {
        return nullptr;
    }

    // Gera um índice aleatório entre 0 e o tamanho do vetor - 1
    int indiceSorteado = rand() % escolhas.size();

    return escolhas[indiceSorteado];
}



