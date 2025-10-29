
#include "ComandoJardim.h"
#include "Jardim.h"

bool ComandoJardim::executa(Simulador &sim, std::istringstream & params) const{
    if(sim.devolveJardim() != nullptr) return false;
    int nL, nC;
    if(!(params >> nL)) return false;
    if(!(params >> nC)) return false;
    if(nL == 0 || nC == 0) return false;

    sim.criaJardim(nL,nC);
    return true;
}

