
#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <string>
#include <vector>
#include <memory>
#include "Ferramenta.h"
#include "BocadoSolo.h"

using namespace std;

class Jardineiro {
private:
    BocadoSolo* localAtual = nullptr; //onde esta no jardim
    bool dentroDoJardim = false;

    vector<unique_ptr<Ferramenta>> ferramentas; //inventario
    //por agora pus assim mas secalhar isso muda-se vi que com o vector ajuda
    //mas nao o sei usar muito bem
    Ferramenta* ferramentaNaMao = nullptr;//ativa

    int movimentosRestantes = 10;
    int colheitasRestantes = 5;
    int plantasRestantes = 2;
    //bool podeEntrarSair = true; jorge sugeriu isto mas nao sei se meto


public:
    Jardineiro();
    ~Jardineiro();

    //estados lá do jardineiro e assim
    bool estaDentro() const; //resposta rápida a “está dentro ou fora?”
                             //é conveniente para os comandos
    BocadoSolo* getLocalAtual() const;
    void entrarNoJardim(BocadoSolo* novoLocal);
    void sairDoJardim();
    void mover(const string& direcao); //isto depende depois de como os comandos foram feitos então

    //pa tratar das ferramentas
    void adicionarFerramenta(unique_ptr<Ferramenta> f); //tenho que ver melhor isto
    void pegarFerramenta();
    Ferramenta* getFerramentaNaMao() const;

    //acoes
    void aplicarFerramenta();
    void resetTurno(); //por agora (turno = instante)

    string getInfo() const;
};



#endif
