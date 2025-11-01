
#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <string>
#include <vector>
#include "Ferramenta.h"
#include "BocadoSolo.h"

using namespace std;

class Jardineiro {

    BocadoSolo* localAtual;
    bool dentroDoJardim;

    vector<Ferramenta*> ferramentas;
    Ferramenta* ferramentaNaMao;//ativa

    int movimentosRestantes;
    int colheitasRestantes;
    int plantasRestantes;

public:
    Jardineiro();
    ~Jardineiro();

    bool estaDentro() const { return dentroDoJardim; }
    BocadoSolo* getLocalAtual() const { return localAtual;}
    void mudaLocal(BocadoSolo * b) { localAtual = b; };

    //pa tratar das ferramentas
    void adicionarFerramenta(Ferramenta* f);

    void pegaFerramenta();
    void largaFerramenta();

    Ferramenta* getFerramentaNaMao() const;

    //acoes
    void aplicarFerramenta();
    void resetTurno();

    string getInfo() const;
};



#endif
