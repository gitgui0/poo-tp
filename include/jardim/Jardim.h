
#ifndef JARDIM_H
#define JARDIM_H

#include "BocadoSolo.h"
#include <string>
#include <memory>

class Jardim {

  public:

    Jardim() = default;
    Jardim(int nLinhas, int nColunas);
    explicit Jardim(const Jardim& j);
    ~Jardim();

    Ferramenta* apanharFerramenta(BocadoSolo* solo);
    std::pair<int,int> getPosicaoBocado(BocadoSolo* b) const noexcept;
    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    void multiplica();

    std::string mostraJardim() const noexcept;

    BocadoSolo * getBocado(int l, int c);

    std::unique_ptr<Jardim> clone() const {
      return std::make_unique<Jardim>(*this);
    }

  private:

    static Ferramenta* geraFerramentaAleatoria();
    void colocaFerramentasIniciais();

    int nLinhas;
    int nColunas;

    BocadoSolo **area;

    static int instantes;


};



#endif
