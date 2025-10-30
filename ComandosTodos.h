
#ifndef COMANDOSTODOS_H
#define COMANDOSTODOS_H

#include "Comando.h"

class ComandoAvanca : public Comando {

public:
    ComandoAvanca() = default;
    bool executa(Simulador &sim, std::istringstream & params ) const override;
    const char* getNome() override { return "avanca"; }

};

class ComandoJardim : public Comando {
public:
    ComandoJardim() = default;
    bool executa(Simulador &sim, std::istringstream & params ) const override;
    const char* getNome() override { return "jardim"; }
};

class ComandoEntraJardim : public Comando {
public:
    ComandoEntraJardim() = default;
    bool executa(Simulador & sim, std::istringstream & params) const override;
    const char* getNome() override { return "entra"; }
};

#endif
