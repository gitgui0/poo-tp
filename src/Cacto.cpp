#include "Cacto.h"
#include <iostream>
#include <vector>

Cacto::Cacto() : Planta(0,0,'c',"Neutra") {};
Cacto::Cacto(int agua, int nutrientes) : Planta(agua,nutrientes,'c',"Neutra") {};
Cacto::~Cacto(){ std::cout << "Desconstrutor cacto " << std::endl;}

void Cacto::cadaInstante(BocadoSolo* b) {
    int absorveNutri = ( b->getNutrientes() > 5 ? 5 : b->getNutrientes());
    int absorveAgua = (b->getAgua() >= 1 ?  (b->getAgua() * 0.25 == 0 ? 1 : b->getAgua()) : 0);

    colocarNutrientes(obterNutrientes() + absorveNutri);
    colocarAgua(obterAgua() + absorveAgua);

    b->setNutrientes(b->getNutrientes() - absorveNutri);
    b->setAgua(b->getAgua() - absorveAgua);
}
void Cacto::multiplica(BocadoSolo *b, Jardim* j) {
    if (b==nullptr)
        throw std::runtime_error("Erro inesperado. Esse solo nao existe");

    //Condicoes para multiplicar (neste caso e nele proprio mas pode ser na posicao vizinnha, ou seja, no geraVizinho
    if (!( obterNutrientes() > 100 && obterAgua() > 50 ))
        return;

    BocadoSolo* vizinho = geraVizinho(b,j);
    if (vizinho==nullptr)
        return;

    int agua= obterAgua() / 2;
    int nutrientes = obterNutrientes() / 2;

    Planta* p  = new Cacto(agua,nutrientes);

    colocarAgua(agua);
    colocarNutrientes(nutrientes);

    vizinho->setPlanta(p);

}


BocadoSolo* Cacto::geraVizinho(BocadoSolo *b, Jardim* j) const {
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
                { escolhas.push_back(vizinho); }
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



