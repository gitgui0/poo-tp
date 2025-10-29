
#ifndef COMANDOAVANCA_H
#define COMANDOAVANCA_H

#include "Comando.h"

class ComandoAvanca : public Comando {

  public:
      ComandoAvanca() = default;
      bool executa(Simulador &sim, std::istringstream & params ) const override;
      const char* getNome() override { return "avanca"; }

};



#endif
