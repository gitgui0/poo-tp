#include "ComandosTodos.h"

#include <iostream>
#include <string>

bool ComandoAvanca::executa(Simulador &sim, std::istringstream & params) const{
    int n;
    if (!(params >> n)) { //tenta ler dos params, se nao, fica com o default
        n = 1;
    }
    std::cout << "comando avanca com n=" << std::to_string(n) << std::endl;
    return true;
}


bool ComandoJardim::executa(Simulador &sim, std::istringstream & params) const{
    if(sim.devolveJardim() != nullptr) return false;
    int nL, nC;
    if(!(params >> nL)) return false;
    if(!(params >> nC)) return false;
    if(nL == 0 || nC == 0) return false;

    sim.criaJardim(nL,nC);
    return true;
}