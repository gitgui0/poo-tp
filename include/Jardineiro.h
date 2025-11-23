
#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <string>
#include <vector>
#include "Ferramenta.h"
#include "BocadoSolo.h"
#include "jardim.h" //por agr

using namespace std;

class Jardineiro {

    BocadoSolo* localAtual;
    bool dentroDoJardim;

    vector<Ferramenta*> ferramentas;
    Ferramenta* ferramentaNaMao;//ativa

    void processarMovimento(Jardim* jardim);
    int movimentosRestantes;
    int colheitasRestantes;
    int plantasRestantes;

public:
    Jardineiro();
    ~Jardineiro();

    bool estaDentro() const { return dentroDoJardim;}
    void setEstaDentro(bool s) {dentroDoJardim = s;}
    BocadoSolo* getLocalAtual() const { return localAtual;}
    void mudaLocal(BocadoSolo * b) { localAtual = b;}

    //pa tratar das ferramentas
    void adicionarFerramenta(Ferramenta* f);

    void pegaFerramenta(Ferramenta* f);
    void largaFerramenta();

    vector< Ferramenta* > devolveFerramentas() const noexcept{ return ferramentas;}

    Ferramenta* getFerramentaNaMao() const;

    //acoes
    void aplicarFerramenta();
    void resetTurno();

    string getInfo() const;
};



#endif
