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
void ComandoLPlantas::executa(Simulador &sim, std::istringstream &) const {

    Jardim* jardim = sim.devolveJardim();
    if (jardim == nullptr)
        throw std::runtime_error("O jardim nao existe");

    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {
            BocadoSolo* b= jardim->getBocado(i,j);
            Planta* p = b->getPlanta();
            if (p == nullptr)
                continue;
            char l = p->getLetra();
            string planta;
            if (l=='c') planta = "Cacto";
            else if (l=='e') planta = "Erva Daninha";
            else if (l=='x') planta = "Orquidea";
            else if (l=='r') planta = "Roseira";

            std::cout << "(" << Simulador::intParaChar(i) << "," << Simulador::intParaChar(j) << ") : " << planta << endl;
            std::cout << "Planta - Agua: " << p->obterAgua() << " - Nutrientes: " << p->obterNutrientes() << endl;
            std::cout << "Solo - Agua: " << b->getAgua() << " - Nutrientes: " << b->getNutrientes() << endl;
            std::cout << "\n";
        }
    }

    std::cout << sim.mostraJardim() << endl;
}


//lplanta <l><c>

void ComandoLPlanta::executa(Simulador &sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    if (jardim == nullptr) throw std::runtime_error("O jardim nao existe");

    char l, c;
    if (!(params >> l >> c)) throw std::runtime_error("Faltam parametros (linha coluna)");

    BocadoSolo* b = jardim->getBocado(Simulador::charParaInt(l), Simulador::charParaInt(c));
    if (b == nullptr) throw std::runtime_error("Posicao invalida");

    Planta* p = b->getPlanta();
    if (p == nullptr) {
        std::cout << "Nao existe planta na posicao " << l << c << std::endl;
        return;
    }

    // Reutilizando a lógica de display (podes ajustar a formatação)
    std::cout << "Posicao " << l << c << ": " << p->getLetra() << " (" << p->getBeleza() << ")" << endl;
    std::cout << "Planta  -> Agua: " << p->obterAgua() << " | Nutrientes: " << p->obterNutrientes() << endl;
    std::cout << "Solo    -> Agua: " << b->getAgua() << " | Nutrientes: " << b->getNutrientes() << endl;
}

void ComandoLArea::executa(Simulador &sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    if (jardim == nullptr)
        throw std::runtime_error("O jardim nao existe");

    std::cout << "--- Listagem da Area (Apenas posicoes ocupadas) ---" << endl;

    bool encontrouAlgo = false;

    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {

            BocadoSolo* b = jardim->getBocado(i, j);

            if (b->getPlanta() != nullptr || b->getFerramenta() != nullptr || b->estaJardineiro()) {

                encontrouAlgo = true;

                char linhaChar = Simulador::intParaChar(i);
                char colChar = Simulador::intParaChar(j);

                std::cout << "[" << linhaChar << colChar << "] ";

                if (b->estaJardineiro()) {
                    std::cout << "<JARDINEIRO> ";
                }

                if (b->getPlanta() != nullptr) {
                    std::cout << "Planta: " << b->getPlanta()->getLetra() << " ";
                }

                if (b->getFerramenta() != nullptr) {
                    std::cout << "Ferramenta: " << b->getFerramenta()->getLetra() << " ";
                }

                std::cout << "| Solo(Agua:" << b->getAgua() << ", Nutri:" << b->getNutrientes() << ")" << endl;
            }
        }
    }

    if (!encontrouAlgo) {
        std::cout << "O jardim esta completamente vazio de objetos." << endl;
    }
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

    // tenta ler o parametro opcional n
    params >> n;

    // Converter centro para coordenadas
    int centroL = Simulador::charParaInt(l);
    int centroC = Simulador::charParaInt(c);

    // Verificar se o centro é válido
    if (jardim->getBocado(centroL, centroC) == nullptr)
        throw std::runtime_error("Posicao central invalida");

    // O std::max(0, centroL - n) garante que nao vai para índices negativos
    // O std::min(jardim->getLinhas() - 1, centroL + n) garante que não passamos do tamanho do jardim
    int inicioL = std::max(0, centroL - n);
    int fimL = std::min(jardim->getLinhas() - 1, centroL + n);

    int inicioC = std::max(0, centroC - n);
    int fimC = std::min(jardim->getColunas() - 1, centroC + n);

    std::cout << "--- Info Solo (Centro: " << l << c << " | Raio: " << n << ") ---" << endl;


    for (int i = inicioL; i <= fimL; i++) {
        for (int j = inicioC; j <= fimC; j++) {

            BocadoSolo* b = jardim->getBocado(i, j);

            char linhaOut = Simulador::intParaChar(i);
            char colOut = Simulador::intParaChar(j);

            std::cout << "> [" << linhaOut << colOut << "] "
                      << "Agua: " << b->getAgua()
                      << " | Nutri: " << b->getNutrientes();
            if (b->estaJardineiro()) std::cout << " [Jardineiro]";

            if (b->getPlanta() != nullptr) {
                std::cout << " [Planta: " << b->getPlanta()->getLetra() << "]";
            }

            if (b->getFerramenta() != nullptr) {
                std::cout << " [Ferr: " << b->getFerramenta()->getLetra() << "]";
            }

            std::cout << endl;
        }
    }
}
void ComandoLFerr::executa(Simulador & sim, std::istringstream &) const {
    int i=1;
    Jardineiro* jardineiro = sim.devolveJardineiro();
    if ( jardineiro->devolveFerramentas().empty() && jardineiro->getFerramentaNaMao() == nullptr) {
        std::cout << "Nao ha ferramentas no inventario.\n";
        return;
    }
    if (jardineiro->getFerramentaNaMao() != nullptr)
        std::cout << "FERRAMENTA NA MAO - " << jardineiro->getFerramentaNaMao() << endl;
    for (Ferramenta* f : jardineiro->devolveFerramentas()) {
        if (i>1) std::cout << "\n";
        if (f!=nullptr) {
            std::cout << f;
            i++;
        }
    }
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