#include "Jardim.h"

#include <sstream>
#include <random>

#include "Regador.h"
#include "Adubo.h"
#include "TesouraPoda.h"
#include "AceleradorCrescimento.h"

#include "Planta.h"

using namespace std;



Jardim::Jardim(int nLinhas, int nColunas)
    : nLinhas(nLinhas), nColunas(nColunas), instantes(0)
{
    // Criação da matriz de objetos
    area = new BocadoSolo*[nLinhas];

    for (int i = 0; i < nLinhas; ++i) {
        area[i] = new BocadoSolo[nColunas];
    }

    colocaFerramentasIniciais();
}

Jardim::Jardim(const Jardim& outro) {
    nLinhas = outro.nLinhas;
    nColunas = outro.nColunas;
    instantes = outro.instantes;

    // Deep copy
    area = new BocadoSolo*[nLinhas];
    for (int i = 0; i < nLinhas; ++i) {
        area[i] = new BocadoSolo[nColunas];
        for (int j = 0; j < nColunas; ++j) {
            // Deep copy a usar o operator = overload do bocadoSolo
            area[i][j] = outro.area[i][j];
        }
    }

}

Jardim::~Jardim() {
    for(int i = 0; i < nLinhas; ++i) {
        delete[] area[i];
    }
    delete[] area;
}

Ferramenta* Jardim::apanharFerramenta(BocadoSolo* solo) {
    if (solo == nullptr) {
        return nullptr;
    }

    // Tentar retirar do solo
    Ferramenta* f = solo->retiraFerramenta();

    //Se apanhamos algo, gerar uma nova noutro local
    if (f != nullptr) {
        int novaL, novaC;

        // Tenta encontrar uma posição vazia (100 tentativas)
        for(int i = 0; i < 100; i++) {
            novaL = rand() % nLinhas;
            novaC = rand() % nColunas;

            // Vamos buscar o solo da nova posição aleatória
            BocadoSolo* soloDestino = getBocado(novaL, novaC);

            // CORREÇÃO AQUI:
            // Em vez de !soloDestino->temFerramenta(), verificamos se o get é nulo
            if (soloDestino != nullptr && soloDestino->getFerramenta() == nullptr) {
                soloDestino->setFerramenta(geraFerramentaAleatoria());
                break;
            }
        }
    }
    return f;
}

Ferramenta* Jardim::geraFerramentaAleatoria() {
    random_device rd;
    mt19937 gen(rd());
    // 0: Regador, 1: Adubo, 2: TesouraPoda, 3: AceleradorCrescimento
    uniform_int_distribution<int> distrib(0, 3);
    int tipo = distrib(gen);

    switch (tipo) {
        case 0: return new Regador();
        case 1: return new Adubo();
        case 2: return new TesouraPoda();
        case 3: return new AceleradorCrescimento();
        default: return nullptr;
    }
}

void Jardim::colocaFerramentasIniciais() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randL(0, nLinhas - 1); // Linhas aleatorias
    uniform_int_distribution<int> randC(0, nColunas - 1); // Colunas aleatorias

    int ferramentasColocadas = 0;
    int maximo = (nColunas * nLinhas < 3 ? nColunas * nLinhas : 3 );

    while (ferramentasColocadas < maximo) {
        int l = randL(gen);
        int c = randC(gen);

        BocadoSolo* bocado = getBocado(l, c);

        // verificar se existe ferramentauma ferramenta no bocado aleatorio
        if (bocado->getFerramenta() != nullptr) continue;

        Ferramenta* f = geraFerramentaAleatoria();
        if (f == nullptr) continue;

       bocado->setFerramenta(f);
       ferramentasColocadas++;
    }
}

int Jardim::getLinhas() const noexcept { return nLinhas; };
int Jardim::getColunas() const noexcept { return nColunas; };

string Jardim::mostraJardim() const noexcept {
    ostringstream oss;
    char l = 'A';
    int i = 0;
    oss << " "; // espaco inicial
    while (i < nColunas) {
        oss << l;
        l++; // ascii
        i++;
    }
    oss << "\n"; // acabou a linha com ABCD...
    l = 'A';

    for(int i = 0; i < nLinhas; ++i) {
        oss << l;
        for (int j = 0; j < nColunas; j++)
            oss << area[i][j].mostra();
        oss << "\n";
        l++; // ascii
    }
    return oss.str();
}

BocadoSolo* Jardim::getBocado(int l, int c) {
    if (l > nLinhas-1 || l < 0  || c > nColunas-1 || c < 0) return nullptr;
    return &area[l][c];
}

BocadoSolo *Jardim::getBocadoDoJardineiro() {
    for (int i = 0; i < nLinhas; i++ ) {
        for (int j = 0; j < nColunas; j++) {
            if (area[i][j].estaJardineiro()) {
                return &area[i][j];
            }
        }
    }
    return nullptr;
}


std::pair<int,int> Jardim::getPosicaoBocado(BocadoSolo* b) const noexcept {
    for (int i = 0; i < nLinhas; i++) {
        for (int j = 0; j < nColunas; j++) {
            if (&area[i][j] == b) {
                return std::pair<int,int>(i,j);
            }
        }
    }
    throw std::runtime_error("[ERRO INTERNO] Esse bocado e invalido.");
}

void Jardim::processaTurno() {

    for (int i = 0; i < nLinhas; i++) {
        for (int j = 0; j < nColunas; j++) {
            BocadoSolo* b = &area[i][j];
            Planta * p = b->getPlanta();

            bool plantaMorreu = false;

            if (p)
                plantaMorreu = p->cadaInstante(b,this);

            if (plantaMorreu)
                b->setPlanta(nullptr);

            if (p!=nullptr)
                p->multiplica(b,this);
        }
    }
}


bool Jardim::colhe(int l, int c) {
    BocadoSolo& b = area[l][c];
    if (b.getPlanta()==nullptr)
        return false;

    b.setPlanta(nullptr);
    return true;
}

void Jardim::planta(int l, int c, char planta) {
    BocadoSolo& b = area[l][c];

    // Ja existe uma planta no sitio
    if (b.getPlanta() != nullptr)
        throw std::runtime_error("Nao e possivel colocar uma planta nessa posicao.");

    Planta* novaPlanta = Planta::criar(planta);

    b.setPlanta(novaPlanta);
}


