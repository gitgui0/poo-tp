
#ifndef JARDIM_H
#define JARDIM_H

#include "BocadoSolo.h"
#include <string>

class Jardim {

  public:

    Jardim() = default;
    Jardim(int nLinhas, int nColunas);
    ~Jardim();
  //o jardim é tipo o meio termo entre a ferramenta do
  //bocado de solo e oo jardineiro
    Ferramenta* apanharFerramenta(int l, int c);
  //Quando o jardineiro pede para apanhar numa posição, o jardim entrega a ferramenta e cria imediatamente uma nova noutro sítio aleatório
    int getLinhas() const noexcept;
    int getColunas() const noexcept;

    std::string mostraJardim() const noexcept;

    BocadoSolo * getBocado(int l, int c);



  private:

    static Ferramenta* geraFerramentaAleatoria();
    void colocaFerramentasIniciais();

    int nLinhas;
    int nColunas;

    BocadoSolo **area;

    static int instantes;


};



#endif
