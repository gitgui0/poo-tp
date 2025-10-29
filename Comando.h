
#ifndef COMANDO_H
#define COMANDO_H

#include <sstream>

// ************** IMPORTANTE *********************
// em vez do include, para nao haver um loop de includes
class Simulador;


class Comando {

    public:
      virtual bool executa(Simulador &sim, std::istringstream & params) const = 0;
      virtual const char* getNome() = 0;
      Comando() = default;
      ~Comando() = default;
};



#endif
