#include "ComandosTodos.h"
#include "Ferramenta.h"
#include "Adubo.h"
#include "Regador.h"
#include "TesouraPoda.h"
#include "AceleradorCrescimento.h"

#include "Planta.h"
#include "Cacto.h"
#include "ErvaDaninha.h"
#include "Orquidea.h"
#include "Roseira.h"

#include "Jardineiro.h"
#include "Jardim.h"
#include "BocadoSolo.h"
#include <iostream>
#include <fstream>
#include <Settings.h>

using namespace std;

// ===========================================================
// Implementação dos Comandos
// ===========================================================

// avanca [n]
void ComandoAvanca::executa(Simulador &sim, std::istringstream &params) const {
    int n;

    if (!(params >> n)) {
        n = 1; // se o user não meter nada, avança 1 por default
    }

    if (n < 1)
        throw std::runtime_error("Valor invalido para o parametro [n]");

    for (int i= 0; i < n; i++) {
        sim.avancaInstante();
    }

    std::cout << "Instantes: " << sim.devolveJardim()->getInstantes() << endl;
    std::cout << sim.mostraJardim();
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
    cout << sim.mostraJardim() << endl;
}


// entra <l><c>
void ComandoEntraJardim::executa(Simulador &sim, std::istringstream &params) const {

    char l, c;

    if (!(params >> l) || !(params >> c))
        throw std::runtime_error("Nao foi enviada uma posicao");

    sim.entraNoJardim(l,c);

    cout << sim.mostraJardim();
}

// gestão e gravação
void ComandoGrava::executa(Simulador &sim, std::istringstream &params) const {
    std::string nome;
    if (!(params >> nome)) {
        throw std::runtime_error("Falta o nome para gravar (ex: grava save1)");
    }
    sim.gravarJardim(nome);
    std::cout << "O jardim foi gravado com sucesso." << endl;
    cout << sim.mostraJardim();
}

void ComandoRecupera::executa(Simulador &sim, std::istringstream &params) const {
    std::string nome;
    if (!(params >> nome)) {
        throw std::runtime_error("Falta o nome do save a recuperar.");
    }
    sim.recuperarJardim(nome);

    std::cout << "O jardim foi recuperado com sucesso." << endl;
    std::cout << sim.mostraJardim();
}
void ComandoApaga::executa(Simulador &sim, std::istringstream &params) const {
    std::string nome;
    if (!(params >> nome)) {
        throw std::runtime_error("Falta o nome do save a apagar.");
    }
    sim.apagarJardim(nome);
}
void ComandoExecuta::executa(Simulador &sim, std::istringstream & params) const {
    std::string nomeFicheiro;

    if (!(params >> nomeFicheiro))
        throw std::runtime_error("Falta o nome do ficheiro");

    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o ficheiro: " + nomeFicheiro);
    }

    std::string linha;
    std::cout << ">>> A iniciar execucao do ficheiro: " << nomeFicheiro << " <<<" << endl;

    // le linha a linha do ficheiro
    while (std::getline(ficheiro, linha)) {

        if (linha.empty()) continue;

        std::cout << ">> [Ficheiro] Executando: " << linha << endl;

        try {
            sim.executa(linha);
        } catch (const std::exception &e) {
            std::cout << "Erro na linha do ficheiro: " << e.what() << endl;
        }
    }

    std::cout << ">>> Fim da execucao do ficheiro <<<" << endl;

    // o ficheiro fecha sozinho quando sai do scope
}

// listagens
// lplantas
void ComandoLPlantas::executa(Simulador &sim, std::istringstream &) const {
    std::cout << sim.listaPlantas();
}

//lplanta <l><c>

void ComandoLPlanta::executa(Simulador &sim, std::istringstream & params) const {

    char l, c;
    if (!(params >> l >> c)) throw std::runtime_error("Faltam parametros (linha coluna)");

    std::cout << sim.listaPlanta(l, c);
}

void ComandoLArea::executa(Simulador &sim, std::istringstream & params) const {
    std::cout << sim.listaArea();
}

//lsolo <l><c> [n]
void ComandoLSolo::executa(Simulador &sim, std::istringstream & params) const {

    Jardim* jardim = sim.devolveJardim();
    if (jardim == nullptr)
        throw std::runtime_error("O jardim nao existe");

    char l, c;
    int n = 0; // O raio é 0 por defeito

    if (!(params >> l >> c))
        throw std::runtime_error("Faltam parametros (linha coluna)");

    // tenta ler o parametro opcional n, se falhar fica 0
    params >> n;

    std::cout << sim.listaSolo(l, c, n);
}
void ComandoLFerr::executa(Simulador & sim, std::istringstream &) const {
    std::cout << sim.listaFerramentas();
}

// ações diretas
void ComandoColhe::executa(Simulador &sim, std::istringstream &params) const {

    char l,c;

    if (!(params >> l))
        throw std::runtime_error("Falta especificar a linha da posicao");

    if (!(params >> c))
        throw std::runtime_error("Falta especificar a coluna da posicao");

    sim.colherPlanta(l,c);

    std::cout << sim.mostraJardim();
}
void ComandoPlanta::executa(Simulador &sim, std::istringstream & params) const {

    char l,c, planta;

    if (!(params >> l))
        throw std::runtime_error("Falta especificar a linha da posicao");

    if (!(params >> c))
        throw std::runtime_error("Falta especificar a coluna da posicao");

    if (!(params >> planta))
        throw std::runtime_error("Falta especificar o tipo de planta");

    sim.planta(l,c,planta);
    std:: cout << sim.mostraJardim();
}
void ComandoLarga::executa(Simulador &sim, std::istringstream &) const {
    sim.devolveJardineiro()->largaFerramenta();
}
void ComandoPega::executa(Simulador & sim, std::istringstream & params) const {

    int num;
    if (!(params >> num))
        throw std::runtime_error("Falta especificar o numero de serie da ferramenta");

    sim.pegaFerramenta(num);
}
void ComandoCompra::executa(Simulador & sim, std::istringstream & params) const {
    char tipo;
    if (!(params >> tipo))
        throw std::runtime_error("Falta especificar o tipo de ferramenta a comprar (g, a, t, z)");

    sim.compraEAdiciona(tipo);
}


// movimento do jardineiro
void ComandoMoveEsquerda::executa(Simulador & sim, std::istringstream & params) const {
    sim.moveJardineiro(-1,0);
    cout << sim.mostraJardim();
}
void ComandoMoveDireita::executa(Simulador &sim, std::istringstream & params) const {
    sim.moveJardineiro(1,0);
    cout << sim.mostraJardim();
}
void ComandoMoveCima::executa(Simulador & sim, std::istringstream & params) const {
    sim.moveJardineiro(0,-1);
    cout << sim.mostraJardim();
}
void ComandoMoveBaixo::executa(Simulador &sim, std::istringstream & params) const {
    sim.moveJardineiro(0,1);
    cout << sim.mostraJardim();
}

void ComandoSai::executa(Simulador &sim, std::istringstream &params) const {
    sim.saiDoJardim();
    cout << sim.mostraJardim();
}


// fim do simulador
void ComandoFim::executa(Simulador &sim, std::istringstream &params) const {
    sim.para();
}