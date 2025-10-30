#include "ComandosTodos.h"

#include <iostream>
#include <string>

void ComandoAvanca::executa(Simulador &sim, std::istringstream & params) const{
    int n;
    if (!(params >> n)) { //tenta ler dos params, se nao, fica com o default
        n = 1;
    }
    if (n < 1) throw std::runtime_error("Valor invalido para o parametro [n]");
    std::cout << "comando avanca com n=" << std::to_string(n) << std::endl;
}


void ComandoJardim::executa(Simulador &sim, std::istringstream & params) const{
    if(sim.devolveJardim() != nullptr) throw std::runtime_error("Ja existe um jardim");
    int nL, nC;
    if(!(params >> nL)) throw std::runtime_error("Nao foi enviado o primeiro parametro");;
    if(!(params >> nC)) throw std::runtime_error("Nao foi enviado o segundo parametro");;
    if(nL <= 0 || nC <= 0) throw std::runtime_error("Valor de parametro invalido");;

    sim.criaJardim(nL,nC);
}

void ComandoEntraJardim::executa(Simulador & sim, std::istringstream & params) const {
    if (sim.devolveJardim() == nullptr)
        throw std::runtime_error("Nao existe jardim");;
    int l,c;

    if (!(params>>l) || !(params>>c))
        throw std::runtime_error("Nao foi enviada uma posicao");

    Jardim* jar = sim.devolveJardim();
    BocadoSolo* b = jar->getBocado(l,c);
    Jardineiro* j = sim.devolveJardineiro();

    if (j == nullptr || b == nullptr )
        throw std::runtime_error("Posicao invalida");

    if (j->getLocalAtual() != nullptr )
        // teletransportar q diz no enunciado
        j->getLocalAtual()->removeJardineiro();

    j->mudaLocal(b);
    b->colocaJardineiro();

}