#include "ComandosTodos.h"
#include "Ferramenta.h"
#include "Adubo.h"
#include "Regador.h"
#include "TesouraPoda.h"
#include "AceleradorCrescimento.h"

#include <iostream>

// ===========================================================
// Comandos já funcionais
// ===========================================================

// avanca [n]
void ComandoAvanca::executa(Simulador &sim, std::istringstream &params) const {
    int n;
    if (sim.devolveJardim() == nullptr)
        throw std::runtime_error("Nao existe jardim. ");
    if (!(params >> n)) {
        n = 1; // se o user não meter nada, avança 1 por default
    }

    if (n < 1)
        throw std::runtime_error("Valor invalido para o parametro [n]");

    for (int i= 0; i < n; i++) sim.avancaInstante();
    std::cout << sim.getInstantes() << endl;
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
void ComandoLFerr::executa(Simulador & sim, std::istringstream &) const {
    int i=1;
    Jardineiro* jardineiro = sim.devolveJardineiro();
    if ( jardineiro->devolveFerramentas().empty()) {
        std::cout << "Nao ha ferramentas no inventario.\n";
        return;
    }
    for (Ferramenta* f : jardineiro->devolveFerramentas()) {
        if (i>1) std::cout << "\n";
        std::cout << i << ". " << f->mostra();
        i++;
    }
}

// ações diretas
void ComandoColhe::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] colhe (a implementar)" << std::endl;
}
void ComandoPlanta::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] planta (a implementar)" << std::endl;
}
void ComandoLarga::executa(Simulador &sim, std::istringstream &) const {
    if (sim.devolveJardim() == nullptr)
        throw std::runtime_error("Nao existe jardim criado");
    sim.devolveJardineiro()->largaFerramenta();
}
void ComandoPega::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] pega (a implementar)" << std::endl;
}
void ComandoCompra::executa(Simulador & sim, std::istringstream & params) const {
    char tipo;
    if (!(params >> tipo))
        throw std::runtime_error("Falta especificar o tipo de ferramenta a comprar (g, a, t, z)");

    Ferramenta* novaFerramenta = nullptr;

    switch (tolower(tipo)) {
        case 'g':
            novaFerramenta = new Regador();
        break;
        case 'a':
            novaFerramenta = new Adubo();
        break;
        case 't':
            novaFerramenta = new TesouraPoda();
        break;
        case 'z':
            novaFerramenta = new AceleradorCrescimento();
        break;
        default:
            throw std::runtime_error("Tipo de ferramenta invalida. Use g, a, t, ou z.");
    }

    // A ferramenta comprada é adicionada ao inventário
    sim.devolveJardineiro()->adicionarFerramenta(novaFerramenta);
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
