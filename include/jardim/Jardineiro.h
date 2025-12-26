
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

    int entradasSaidasRestantes;

public:
    Jardineiro();
    ~Jardineiro();

    bool estaDentro() const { return dentroDoJardim;}
    void setEstaDentro(bool s) {dentroDoJardim = s;}
    BocadoSolo* getLocalAtual() const { return localAtual;}
    void mudaLocal(BocadoSolo * b) { localAtual = b;}

    void move(BocadoSolo* b);
    void sai();

    //pa tratar das ferramentas
    void adicionarFerramenta(Ferramenta* f);


    void pegaFerramenta(Ferramenta* f);
    void pegaFerramenta();
    void pegaFerramenta(int num);
    void largaFerramenta();

    int getPlantasRestantes() const noexcept { return plantasRestantes;}
    int getColheitasRestantes() const noexcept { return colheitasRestantes;}
    int getMovimentosRestantes() const noexcept { return movimentosRestantes;}
    int getEntradasSaidasRestantes() const noexcept { return entradasSaidasRestantes;}


    void menosPlantasRestantes()  { plantasRestantes--;}
    void menosColheitasRestantes()  { colheitasRestantes--;}
    void menosMovimentosRestantes()  { movimentosRestantes--;}
    void menosEntradasSaidasRestantes()  { entradasSaidasRestantes--;}

    vector< Ferramenta* > devolveFerramentas() const noexcept{ return ferramentas;}

    Ferramenta* getFerramentaNaMao() const;

    //acoes
    void aplicarFerramenta(Jardim* j);
    void resetTurno();

    string getInfo() const;
};



#endif
