#include "Jardim.h"
#include <sstream>

using namespace std;

int Jardim::instantes = 0;

Jardim::Jardim(int nLinhas, int nColunas)
    : nLinhas(nLinhas), nColunas(nColunas)
{
    area = new BocadoSolo*[nLinhas]; // linhas

    for (int i = 0; i < nLinhas; ++i) {
        area[i] = new BocadoSolo[nColunas];  // colunas
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

string Jardim::mostraJardim() const noexcept {
    ostringstream oss;
    char l = 'A';
    int i = 0;
    oss << " "; // espaco inicial
    while (i < nColunas) {
        oss << l;
        l++; // ascii
        i++;
    }
    oss << "\n"; // acabou a linha com ABCD...

    l = 'A';

    for(int i = 0; i < nLinhas; ++i) {
        oss << l;
        for (int j = 0; j < nColunas; j++)
            oss << area[i][j].mostra();
        oss << "\n";
        l++; // ascii
    }
    return oss.str();
}

BocadoSolo * Jardim::getBocado(int l, int c) {
    if (l > nLinhas || l < 0  || c > nColunas || c < 0) return nullptr;
    return &area[l][c];
}