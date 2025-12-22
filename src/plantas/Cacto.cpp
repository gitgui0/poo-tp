#include "Cacto.h"
#include <iostream>
#include <vector>

Cacto::Cacto() : Planta(0,0,'c',"Neutra"), turnosAguaExcessiva(0), turnosNutrientesExcessivos(0) {};
Cacto::Cacto(int agua, int nutrientes) : Planta(agua,nutrientes,'c',"Neutra") {};
Cacto::~Cacto(){ std::cout << "Desconstrutor cacto " << std::endl;}

bool Cacto::cadaInstante(BocadoSolo* b) {

    if (b->getAgua() > 100)
        turnosAguaExcessiva++;
    else
        turnosAguaExcessiva=0;

    if (b->getNutrientes() <= 0)
        turnosNutrientesExcessivos++;
    else
        turnosNutrientesExcessivos=0;

    // Se nutrientes do bocado de solo > 5, entao 5, se nao os nutrientes que tem.
    int absorveNutri = ( b->getNutrientes() > 5 ? 5 : b->getNutrientes());

    // Se agua do bocado de solo maior que 1, se sim - A, se nao 0
    // A - como e um inteiro, temos que verificar se nao fica 0.9, por exemplo.
    // Porque depois ficaria 0, e isso nao faz sentido, entao.
    // Se nao for o caso, fica se logo com os 25% arredondados e pronto.
    int absorveAgua = (b->getAgua() >= 1 ?  (b->getAgua() * 0.25 == 0 ? 1 : b->getAgua() * 0.25) : 0);

    //Colocar a agua e nutrientes na planta. atuais + absorvidos
    colocarNutrientes(obterNutrientes() + absorveNutri);
    colocarAgua(obterAgua() + absorveAgua);

    //Colocar a agua e nutrientes no bocado de solo (b). atuais - absorvidos
    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);

    return turnosAguaExcessiva >= 3 || turnosNutrientesExcessivos >= 3;
}

void Cacto::multiplica(BocadoSolo *b, Jardim* j) {
    if (b==nullptr)
        throw std::runtime_error("Erro inesperado. Esse solo nao existe");

    //Condicoes para multiplicar (neste caso e nele proprio, mas em outras plantas, a condicao
    // teria que estar ser verificada na posicao vizinha, ou seja, na funcao geraVizinho )
    if (!( obterNutrientes() > 100 && obterAgua() > 50 ))
        return;

    BocadoSolo* vizinho = geraVizinho(b,j);
    if (vizinho==nullptr)
        return;

    // variaveis para agua e nutrientes novos, porque o cacto fica com metade da agua
    // e nutrientes que ja tinha, e passa metade para o novo cacto
    int agua= obterAgua() / 2;
    int nutrientes = obterNutrientes() / 2;


    //Criar um cacto com os nutrientes e agua do cacto "pai"
    Planta* p  = new Cacto(agua,nutrientes);


    // Atualizar a gua e nutrienttes do cacto "pai"
    colocarAgua(agua);
    colocarNutrientes(nutrientes);

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



