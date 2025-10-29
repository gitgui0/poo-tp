#include "Jardim.h"

int Jardim::instantes = 0;

Jardim::Jardim(int nLinhas, int nColunas)
    : nLinhas(nLinhas), nColunas(nColunas)
{
    area = new BocadoSolo*[nLinhas];
    for(int i = 0; i < nLinhas; ++i) {
        area[i] = new BocadoSolo[nColunas];
    }
}

Jardim::~Jardim() {
    for(int i = 0; i < nLinhas; ++i) {
        delete[] area[i];
    }
    delete[] area;
}

int Jardim::getLinhas() const noexcept { return nLinhas; };
int Jardim::getColunas() const noexcept { return nColunas; };

