#include "Jardim.h"
#include <sstream>
#include <random>
#include "Regador.h"
#include "Adubo.h"
#include "TesouraPoda.h"
#include "AceleradorCrescimento.h"

using namespace std;

int Jardim::instantes = 0;

Jardim::Jardim(int nLinhas, int nColunas)
    : nLinhas(nLinhas), nColunas(nColunas)
{
    // Criação da matriz de objetos
    area = new BocadoSolo*[nLinhas];

    for (int i = 0; i < nLinhas; ++i) {
        area[i] = new BocadoSolo[nColunas];
    }

    colocaFerramentasIniciais();
}

Jardim::~Jardim() {
    for(int i = 0; i < nLinhas; ++i) {
        delete[] area[i];
    }
    delete[] area;
}

Ferramenta* Jardim::apanharFerramenta(int l, int c) {
    // 1. Obter o ponteiro para o solo usando a função segura getBocado
    BocadoSolo* solo = getBocado(l, c);

    if (solo == nullptr) {
        return nullptr;
    }

    // 2. Tentar retirar do solo
    Ferramenta* f = solo->retiraFerramenta();

    // 3. Se apanhámos algo, gerar uma nova noutro local "por magia"
    if (f != nullptr) {
        int novaL, novaC;
        bool conseguiu = false;

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
                conseguiu = true;
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
    uniform_int_distribution<int> randL(0, nLinhas - 1);
    uniform_int_distribution<int> randC(0, nColunas - 1);

    int ferramentasColocadas = 0;
    int maximo = (nColunas * nLinhas < 3 ? nColunas * nLinhas : 3 );

    while (ferramentasColocadas < maximo) {
        int l = randL(gen);
        int c = randC(gen);

        BocadoSolo* bocado = getBocado(l, c);

        // CORREÇÃO AQUI:
        // Usamos getFerramenta() != nullptr para ver se está ocupado
        if (bocado->getFerramenta() != nullptr) continue;

        Ferramenta* f = geraFerramentaAleatoria();
        if (f == nullptr) continue;

        if (bocado->insere(f)) {
            ferramentasColocadas++;
        } else {
            delete f;
        }
    }
}

int Jardim::getLinhas() const noexcept { return nLinhas; };
int Jardim::getColunas() const noexcept { return nColunas; };

string Jardim::mostraJardim() const noexcept {
    ostringstream oss;
    char l = 'A';
    int i = 0;
    oss << " ";
    while (i < nColunas) {
        oss << l;
        l++;
        i++;
    }
    oss << "\n";
    l = 'A';

    for(int i = 0; i < nLinhas; ++i) {
        oss << l;
        for (int j = 0; j < nColunas; j++)
            oss << area[i][j].mostra();
        oss << "\n";
        l++;
    }
    return oss.str();
}

BocadoSolo* Jardim::getBocado(int l, int c) {
    if (l > nLinhas-1 || l < 0  || c > nColunas-1 || c < 0) return nullptr;
    return &area[l][c];
}