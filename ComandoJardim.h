
#ifndef COMANDOJARDIM_H
#define COMANDOJARDIM_H

#include "Comando.h"

class ComandoJardim : public Comando {
    public:
        ComandoJardim() = default;
        bool executa(Simulador &sim, std::istringstream & params ) const override;
        const char* getNome() override { return "jardim"; }
};



#endif //COMANDOJARDIM_H
