#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "EstaSolo.h"
#include <string>
#include <sstream>

class BocadoSolo;
class Jardim;

class Ferramenta : public EstaSolo {
  public:
    virtual bool aplica(BocadoSolo* b, Jardim* j) = 0;
    virtual std::string mostra() const = 0;
    int getNumSerie() const noexcept { return numSerie; }

    virtual Ferramenta* clone() const = 0;

    explicit Ferramenta(char letra);

  // O 'explicit' evita conversão de char para um objeto Ferramenta, por exemplo, func('a');

  friend std::ostream& operator<<(std::ostream& os, const Ferramenta* f);

  ~Ferramenta() override = 0;

  private:
    static int seq;

    int numSerie;

};

#endif