
#ifndef JARDIM_H
#define JARDIM_H

#include "BocadoSolo.h"
#include <string>

class Jardim {

  public:

    Jardim() = default;
    Jardim(int nLinhas, int nColunas);
    ~Jardim();

    int getLinhas() const noexcept;
    int getColunas() const noexcept;

    std::string mostraJardim() const noexcept;

    BocadoSolo & getBocado(int l, int c);

  private:
    int nLinhas;
    int nColunas;

    BocadoSolo **area;

    static int instantes;

};



#endif
