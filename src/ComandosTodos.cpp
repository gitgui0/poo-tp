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
    Jardim* j = sim.devolveJardim();
    Jardineiro* jardineiro = sim.devolveJardineiro();
    if (j == nullptr)
        throw std::runtime_error("Nao existe jardim. ");

    if (jardineiro == nullptr)
        throw std::runtime_error("Nao existe jardineiro. ");

    if (!(params >> n)) {
        n = 1; // se o user não meter nada, avança 1 por default
    }

    if (n < 1)
        throw std::runtime_error("Valor invalido para o parametro [n]");

    for (int i= 0; i < n; i++) {
        sim.avancaInstante();
        j->multiplica();
        jardineiro->aplicarFerramenta(j);
    }

    std::cout << "Instantes: " << sim.getInstantes() << endl;
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

    if (j->getEntradasRestantes() == 0)
        throw std::runtime_error("O jardineiro ja nao pode entrar outra vez. Tem que avancar o turno.");

    // se o jardineiro já estiver noutro bocado, tira-o de lá primeiro
    if (j->getLocalAtual() != nullptr)
        j->getLocalAtual()->removeJardineiro();

    j->mudaLocal(b);
    b->colocaJardineiro();

    if (j->estaDentro()) {
        if (j->getMovimentosRestantes() <= 0)
            throw std::runtime_error("O jardineiro nao se pode mover mais este turno.");

        j->menosMovimentosRestantes(); // conta como movimento
    }



    j->setEstaDentro(true);

    cout << sim.mostraJardim();
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
void ComandoExecuta::executa(Simulador &sim, std::istringstream & params) const {
    std::string nomeFicheiro;

    // 1. Ler o nome do ficheiro dos parametros
    if (!(params >> nomeFicheiro))
        throw std::runtime_error("Falta o nome do ficheiro");

    // 2. Tentar abrir o ficheiro
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o ficheiro: " + nomeFicheiro);
    }

    std::string linha;
    std::cout << ">>> A iniciar execucao do ficheiro: " << nomeFicheiro << " <<<" << endl;

    // 3. Ler linha a linha até ao fim do ficheiro
    while (std::getline(ficheiro, linha)) {

        // Ignorar linhas vazias
        if (linha.empty()) continue;

        // Feedback visual para saberes o que está a acontecer
        std::cout << ">> [Ficheiro] Executando: " << linha << endl;

        try {
            // A magia acontece aqui: o Simulador trata a linha como se fosse escrita por ti
            sim.executa(linha);

        } catch (const std::exception &e) {
            // Se um comando no ficheiro der erro, mostramos o erro mas continuamos a ler as proximas linhas
            std::cout << "Erro na linha do ficheiro: " << e.what() << endl;
        }
    }

    std::cout << ">>> Fim da execucao do ficheiro <<<" << endl;

    // O ficheiro fecha-se sozinho quando a variavel 'ficheiro' sai de escopo
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
    // 1. Obter o jardim e verificar se existe
    Jardim* jardim = sim.devolveJardim();
    if (jardim == nullptr)
        throw std::runtime_error("O jardim nao existe");

    std::cout << "--- Listagem da Area (Apenas posicoes ocupadas) ---" << endl;

    // Flag para saber se encontrámos alguma coisa no fim
    bool encontrouAlgo = false;

    // 2. Percorrer todas as linhas e colunas (Duplo For)
    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {

            // 3. Obter o bocado atual
            BocadoSolo* b = jardim->getBocado(i, j);

            // 4. A GRANDE CONDICAO: O bocado não está "totalmente vazio"?
            // Verifica se tem Planta OU Ferramenta OU Jardineiro
            if (b->getPlanta() != nullptr || b->getFerramenta() != nullptr || b->estaJardineiro()) {

                encontrouAlgo = true;

                // Converte numeros (0,0) para letras (AA) para o print
                char linhaChar = Simulador::intParaChar(i);
                char colChar = Simulador::intParaChar(j);

                std::cout << "[" << linhaChar << colChar << "] ";

                // 5. Mostra quem está lá
                if (b->estaJardineiro()) {
                    std::cout << "<JARDINEIRO> ";
                }

                if (b->getPlanta() != nullptr) {
                    std::cout << "Planta: " << b->getPlanta()->getLetra() << " ";
                }

                if (b->getFerramenta() != nullptr) {
                    std::cout << "Ferramenta: " << b->getFerramenta()->getLetra() << " ";
                }

                // 6. Mostra sempre o estado do solo (Agua/Nutrientes)
                std::cout << "| Solo(Agua:" << b->getAgua()
                          << ", Nutri:" << b->getNutrientes() << ")" << endl;
            }
        }
    }

    if (!encontrouAlgo) {
        std::cout << "O jardim esta completamente vazio de objetos." << endl;
    }
}

//lsolo <l><c> [n]
void ComandoLSolo::executa(Simulador &sim, std::istringstream & params) const {
    // 1. Validar Jardim
    Jardim* jardim = sim.devolveJardim();
    if (jardim == nullptr)
        throw std::runtime_error("O jardim nao existe");

    char l, c;
    int n = 0; // O raio é 0 por defeito (apenas a própria célula)

    // 2. Ler os parametros obrigatórios (Linha e Coluna)
    if (!(params >> l >> c))
        throw std::runtime_error("Faltam parametros (linha coluna)");

    // 3. Tentar ler o parametro opcional [n]
    // Se não houver mais nada no stream, 'n' fica com o valor 0
    params >> n;

    // Converter centro para coordenadas
    int centroL = Simulador::charParaInt(l);
    int centroC = Simulador::charParaInt(c);

    // Verificar se o centro é válido
    if (jardim->getBocado(centroL, centroC) == nullptr)
        throw std::runtime_error("Posicao central invalida");

    // 4. Calcular os limites do "quadrado" (Matemática para não sair do array)
    // O std::max(0, ...) garante que não vamos para índices negativos
    // O std::min(..., linhas-1) garante que não passamos do tamanho do jardim
    int inicioL = std::max(0, centroL - n);
    int fimL = std::min(jardim->getLinhas() - 1, centroL + n);

    int inicioC = std::max(0, centroC - n);
    int fimC = std::min(jardim->getColunas() - 1, centroC + n);

    std::cout << "--- Info Solo (Centro: " << l << c << " | Raio: " << n << ") ---" << endl;

    // 5. Percorrer a área definida
    for (int i = inicioL; i <= fimL; i++) {
        for (int j = inicioC; j <= fimC; j++) {

            BocadoSolo* b = jardim->getBocado(i, j);

            // Converter índices para letras para o output (ex: AA, AB)
            char linhaOut = Simulador::intParaChar(i);
            char colOut = Simulador::intParaChar(j);

            std::cout << "> [" << linhaOut << colOut << "] "
                      << "Agua: " << b->getAgua()
                      << " | Nutri: " << b->getNutrientes();

            // Mostra o que ocupa o espaço, se houver algo
            if (b->estaJardineiro()) std::cout << " [Jardineiro]";

            // Usamos os getters para ver se tem coisas
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
    if (sim.devolveJardim() == nullptr)
        throw std::runtime_error("O jardim nao existe.");

    char l,c;
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* jardineiro = sim.devolveJardineiro();

    if (jardineiro->getColheitasRestantes() <= 0)
        throw std::runtime_error("Nao pode colher mais plantas neste turno");

    if (!(params >> l))
        throw std::runtime_error("Falta especificar a linha da posicao");

    if (!(params >> c))
        throw std::runtime_error("Falta especificar a coluna da posicao");


    int linha = Simulador::charParaInt(l), coluna = Simulador::charParaInt(c);

    BocadoSolo* b = jardim->getBocado(linha,coluna);

    if (b->getPlanta()==nullptr)
        throw std::runtime_error("Nao existe planta nessa posicao");

    b->setPlanta(nullptr);
    jardineiro->menosColheitasRestantes();

    std:: cout << sim.mostraJardim();
}
void ComandoPlanta::executa(Simulador &sim, std::istringstream & params) const {
    if (sim.devolveJardim() == nullptr)
         throw std::runtime_error("O jardim nao existe.");

    char tipo,l,c;
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* jardineiro = sim.devolveJardineiro();

    if (jardineiro->getPlantasRestantes() <= 0)
        throw std::runtime_error("Nao pode plantar mais plantas neste turno");

    if (!(params >> l))
        throw std::runtime_error("Falta especificar a linha da posicao");

    if (!(params >> c))
        throw std::runtime_error("Falta especificar a coluna da posicao");

    if (!(params >> tipo))
        throw std::runtime_error("Falta especificar o tipo de planta");

    int linha = Simulador::charParaInt(l), coluna = Simulador::charParaInt(c);

    BocadoSolo* b = jardim->getBocado(linha,coluna);

    // Ja existe uma planta no sitio
    if (b->getPlanta() != nullptr)
        throw std::runtime_error("Nao e possivel colocar uma planta nessa posicao.");

    Planta* novaPlanta = nullptr;

    switch (tolower(tipo)) {
        case 'c':
            novaPlanta = new Cacto();
        break;
        case 'e':
            novaPlanta = new ErvaDaninha();
        break;
        case 'x':
            novaPlanta = new Orquidea();
        break;
        case 'r':
            novaPlanta = new Roseira();
        break;
        default:
            throw std::runtime_error("Tipo de planta invalida. Cacto - c, Erva Daninha - e, Orquidea - x, Roseira - r ");
    }

    b->setPlanta(novaPlanta);
    jardineiro->menosPlantasRestantes();


    std:: cout << sim.mostraJardim();
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

    if (j->getMovimentosRestantes()<=0)
        throw std::runtime_error("Nao ha movimentos restantes para este turno");

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
    j->menosMovimentosRestantes();

    cout << sim.mostraJardim();

}
void ComandoMoveDireita::executa(Simulador &sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;

    if (j->getMovimentosRestantes()<=0)
        throw std::runtime_error("Nao ha movimentos restantes para este turno");

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
    j->menosMovimentosRestantes();

    cout << sim.mostraJardim();
}
void ComandoMoveCima::executa(Simulador & sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;

    if (j->getMovimentosRestantes()<=0)
        throw std::runtime_error("Nao ha movimentos restantes para este turno");

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
    j->menosMovimentosRestantes();

    cout << sim.mostraJardim();
}
void ComandoMoveBaixo::executa(Simulador &sim, std::istringstream & params) const {
    Jardim* jardim = sim.devolveJardim();
    Jardineiro* j = sim.devolveJardineiro();
    BocadoSolo* b = j->getLocalAtual(), *novo;

    if (j->getMovimentosRestantes()<=0)
        throw std::runtime_error("Nao ha movimentos restantes para este turno");

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
    j->menosMovimentosRestantes();

    cout << sim.mostraJardim();
}

void ComandoSai::executa(Simulador &sim, std::istringstream &params) const {
    if (sim.devolveJardim() == nullptr)
        throw std::runtime_error("Nao existe jardim criado");

    Jardineiro *j = sim.devolveJardineiro();

    if (j == nullptr)
        throw std::runtime_error("Erro inesperado.");

    if (j->getEntradasRestantes() == 0)
        throw std::runtime_error("O jardineiro ja nao pode sair. Tem que avancar o turno");

    j->getLocalAtual()->removeJardineiro();
    j->mudaLocal(nullptr);
    j->setEstaDentro(false);

    j->menosEntradasRestantes();

    cout << sim.mostraJardim();
}


// fim do simulador
void ComandoFim::executa(Simulador &, std::istringstream &) const {
    std::cout << "[CMD] fim (a implementar)" << std::endl;
}