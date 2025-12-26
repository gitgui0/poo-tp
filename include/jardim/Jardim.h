
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

    int getInstantes() const noexcept { return instantes;}
    void setInstantes(int num=1) noexcept { instantes +=num; }

    void processaTurno();

    bool colhe(int l, int c);
    void planta(int l, int c, char planta);

    std::string mostraJardim() const noexcept;

    BocadoSolo * getBocado(int l, int c);
    BocadoSolo * getBocadoDoJardineiro();


    std::unique_ptr<Jardim> clone() const {
      return std::make_unique<Jardim>(*this);
    }

  private:
    static Ferramenta* geraFerramentaAleatoria();
    void colocaFerramentasIniciais();

    int nLinhas;
    int nColunas;

    BocadoSolo **area;

    int instantes;


};



#endif
