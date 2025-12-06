
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

    int entradasRestantes;

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

    int getPlantasRestantes() const noexcept { return plantasRestantes;}
    int getColheitasRestantes() const noexcept { return colheitasRestantes;}
    int getMovimentosRestantes() const noexcept { return movimentosRestantes;}
    int getEntradasRestantes() const noexcept { return entradasRestantes;}


    void menosPlantasRestantes()  { plantasRestantes--;}
    void menosColheitasRestantes()  { colheitasRestantes--;}
    void menosMovimentosRestantes()  { movimentosRestantes--;}
    void menosEntradasRestantes()  { entradasRestantes--;}

    vector< Ferramenta* > devolveFerramentas() const noexcept{ return ferramentas;}

    Ferramenta* getFerramentaNaMao() const;

    //acoes
    void aplicarFerramenta();
    void resetTurno();

    string getInfo() const;
};



#endif
