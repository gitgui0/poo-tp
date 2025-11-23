#include "ComandosTodos.h"
#include "Ferramenta.h"
#include "Adubo.h"
#include "Regador.h"
#include "TesouraPoda.h"
#include "AceleradorCrescimento.h"

// Includes necessários
#include "Jardineiro.h"
#include "Jardim.h"
#include "BocadoSolo.h"
#include <iostream>

using namespace std;

// ===========================================================
// Implementação dos Comandos
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

    j->setEstaDentro(true);
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
void ComandoPega::executa(Simulador & sim, std::istringstream & params) const {
    Jardineiro *j = sim.devolveJardineiro();
    int num;
    if (!(params >> num))
        throw std::runtime_error("Falta especificar o numero de serie da ferramenta");
    for (Ferramenta *f : j->devolveFerramentas())
        if (f->getNumSerie() == num) {
            j->pegaFerramenta(f);
            return;
        }

    throw std::runtime_error("Essa ferramenta nao esta no inventario");
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
void ComandoMoveEsquerda::executa(Simulador & sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;


    if (jardim == nullptr )
        throw std::runtime_error("Nao existe jardim. ");

    if (b == nullptr)
        throw std::runtime_error("O jardineiro nao esta no jardim.");


    std::pair<int,int> posicao = jardim->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    if (c==0)
        throw std::runtime_error("O movimento nao e possivel.");

    novo = jardim->getBocado(l,c - 1); // -1 porque e para a andar para a esquerda
    b->removeJardineiro(); // remover o jardineiro do bocado atual

    // colocar o jardinieor no bocado novo
    novo->colocaJardineiro();
    j->mudaLocal(novo);


}
void ComandoMoveDireita::executa(Simulador &sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;


    if (jardim == nullptr )
        throw std::runtime_error("Nao existe jardim. ");

    if (b == nullptr)
        throw std::runtime_error("O jardineiro nao esta no jardim.");


    std::pair<int,int> posicao = jardim->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    if (c==jardim->getColunas() - 1)
        throw std::runtime_error("O movimento nao e possivel.");

    novo = jardim->getBocado(l,c + 1); // +1 porque e para a andar para a direita
    b->removeJardineiro(); // remover o jardineiro do bocado atual

    // colocar o jardinieor no bocado novo
    novo->colocaJardineiro();
    j->mudaLocal(novo);
}
void ComandoMoveCima::executa(Simulador & sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;


    if (jardim == nullptr )
        throw std::runtime_error("Nao existe jardim. ");

    if (b == nullptr)
        throw std::runtime_error("O jardineiro nao esta no jardim.");


    std::pair<int,int> posicao = jardim->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    if (l==0)
        throw std::runtime_error("O movimento nao e possivel.");

    novo = jardim->getBocado(l-1 , c); // -1 porque e para a andar para cima
    b->removeJardineiro(); // remover o jardineiro do bocado atual

    // colocar o jardinieor no bocado novo
    novo->colocaJardineiro();
    j->mudaLocal(novo);
}
void ComandoMoveBaixo::executa(Simulador &sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;


    if (jardim == nullptr )
        throw std::runtime_error("Nao existe jardim. ");

    if (b == nullptr)
        throw std::runtime_error("O jardineiro nao esta no jardim.");


    std::pair<int,int> posicao = jardim->getPosicaoBocado(b);
    int l = posicao.first;
    int c = posicao.second;

    if (l==jardim->getLinhas() - 1)
        throw std::runtime_error("O movimento nao e possivel.");

    novo = jardim->getBocado(l + 1,c); // +1 porque e para a andar para baixo
    b->removeJardineiro(); // remover o jardineiro do bocado atual

    // colocar o jardineiro no bocado novo
    novo->colocaJardineiro();
    j->mudaLocal(novo);
}

void ComandoSai::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] sai (a implementar)" << std::endl;
}


// fim do simulador
void ComandoFim::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] fim (a implementar)" << std::endl;
}