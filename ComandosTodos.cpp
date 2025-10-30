#include "ComandosTodos.h"
#include <iostream>
#include <string>

// ===========================================================
// Comandos já funcionais
// ===========================================================

// avanca [n]
void ComandoAvanca::executa(Simulador &sim, std::istringstream &params) const {
    int n;
    if (!(params >> n)) {
        n = 1; // se o user não meter nada, avança 1 por default
    }

    if (n < 1)
        throw std::runtime_error("Valor invalido para o parametro [n]");

    std::cout << "[CMD] avanca " << n << " instante(s)" << std::endl;

    // TODO: chamar o método do simulador quando existir
}


// jardim <linhas> <colunas>
void ComandoJardim::executa(Simulador &sim, std::istringstream &params) const {
    if (sim.devolveJardim() != nullptr)
        throw std::runtime_error("Ja existe um jardim");

    int nL, nC;
    if (!(params >> nL))
        throw std::runtime_error("Falta o primeiro parametro (linhas)");
    if (!(params >> nC))
        throw std::runtime_error("Falta o segundo parametro (colunas)");

    if (nL <= 0 || nL >= 27 || nC <= 0 || nC >= 27)
        throw std::runtime_error("Valores fora dos limites (1 a 26)");

    std::cout << "[CMD] jardim " << nL << "x" << nC << " criado" << std::endl;
    sim.criaJardim(nL, nC);
}


// entra <l><c>
void ComandoEntraJardim::executa(Simulador &sim, std::istringstream &params) const {
    if (sim.devolveJardim() == nullptr)
        throw std::runtime_error("Nao existe jardim criado");

    char l, c;

    if (!(params >> l) || !(params >> c))
        throw std::runtime_error("Nao foi enviada uma posicao");

    Jardim *jar = sim.devolveJardim();
    BocadoSolo *b = jar->getBocado(Simulador::charParaInt(l), Simulador::charParaInt(c));
    Jardineiro *j = sim.devolveJardineiro();

    if (j == nullptr || b == nullptr)
        throw std::runtime_error("Posicao invalida");

    // se o jardineiro já estiver noutro bocado, tira-o de lá primeiro
    if (j->getLocalAtual() != nullptr)
        j->getLocalAtual()->removeJardineiro();

    j->mudaLocal(b);
    b->colocaJardineiro();
}

// isto agora sao so prints basicamente ou "stubs"

// gestão e gravação
void ComandoGrava::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] grava (a implementar)" << std::endl;
}
void ComandoRecupera::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] recupera (a implementar)" << std::endl;
}
void ComandoApaga::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] apaga (a implementar)" << std::endl;
}
void ComandoExecuta::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] executa (a implementar)" << std::endl;
}

// listagens
void ComandoLPlantas::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] lplantas (a implementar)" << std::endl;
}
void ComandoLPlanta::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] lplanta (a implementar)" << std::endl;
}
void ComandoLArea::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] larea (a implementar)" << std::endl;
}
void ComandoLSolo::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] lsolo (a implementar)" << std::endl;
}
void ComandoLFerr::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] lferr (a implementar)" << std::endl;
}

// ações diretas
void ComandoColhe::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] colhe (a implementar)" << std::endl;
}
void ComandoPlanta::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] planta (a implementar)" << std::endl;
}
void ComandoLarga::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] larga (a implementar)" << std::endl;
}
void ComandoPega::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] pega (a implementar)" << std::endl;
}
void ComandoCompra::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] compra (a implementar)" << std::endl;
}


// movimento do jardineiro
void ComandoMoveEsquerda::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] e (mover para a esquerda - a implementar)" << std::endl;
}
void ComandoMoveDireita::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] d (mover para a direita - a implementar)" << std::endl;
}
void ComandoMoveCima::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] c (mover para cima - a implementar)" << std::endl;
}
void ComandoMoveBaixo::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] b (mover para baixo - a implementar)" << std::endl;
}
void ComandoSai::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] sai (a implementar)" << std::endl;
}


// fim do simulador
void ComandoFim::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] fim (a implementar)" << std::endl;
}
