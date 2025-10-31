#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "EstaSolo.h"

class Ferramenta : public EstaSolo {
  public:
    virtual void aplica() = 0;

    explicit Ferramenta(char letra);
  // O 'explicit' evita conversão de char para um objeto Ferramenta, por exemplo, func('a');

  ~Ferramenta() override = 0;

  private:
    static int seq;

    int numSerie;

};

#endif