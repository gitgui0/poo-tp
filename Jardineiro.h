
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
    BocadoSolo* localAtual;
    bool dentroDoJardim;

    vector<unique_ptr<Ferramenta>> ferramentas; //inventario
    //por agora pus assim mas secalhar isso muda-se vi que com o vector ajuda
    //mas nao o sei usar muito bem
    Ferramenta* ferramentaNaMao;//ativa

    int movimentosRestantes;
    int colheitasRestantes;
    int plantasRestantes;
    //bool podeEntrarSair = true; jorge sugeriu isto mas nao sei se meto


public:
    Jardineiro();
    ~Jardineiro();

    bool estaDentro() const { return dentroDoJardim; }
    BocadoSolo* getLocalAtual() const { return localAtual;}
    void mudaLocal(BocadoSolo * b) { localAtual = b; };

    //pa tratar das ferramentas
    void adicionarFerramenta(unique_ptr<Ferramenta> f); //tenho que ver melhor isto

    void pegaFerramenta();
    void largaFerramenta();

    Ferramenta* getFerramentaNaMao() const;

    //acoes
    void aplicarFerramenta();
    void resetTurno(); //por agora (turno = instante)

    string getInfo() const;
};



#endif
