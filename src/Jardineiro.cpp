#include "Jardineiro.h"
#include "Jardim.h"
#include "Ferramenta.h"
#include <iostream>
#include "Settings.h"

using namespace std;

Jardineiro::Jardineiro() : ferramentaNaMao(nullptr),
                           movimentosRestantes(Settings::Jardineiro::max_movimentos),
                           colheitasRestantes(Settings::Jardineiro::max_colheitas),
                           plantasRestantes(Settings::Jardineiro::max_plantacoes),
                           localAtual(nullptr),
                           dentroDoJardim(false),
                           linha(-1), // Inicializar fora do jardim
                           coluna(-1)
{
}

Jardineiro::~Jardineiro() = default;

// --- Ferramentas ---
void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f!=nullptr) ferramentas.push_back(f);
}

void Jardineiro::pegaFerramenta(Ferramenta* f) {
    if (f==nullptr) return;
    largaFerramenta();
    ferramentaNaMao = f;
}

void Jardineiro::largaFerramenta() {
    if (ferramentaNaMao == nullptr) {
        return;
    }
    ferramentas.push_back(ferramentaNaMao);
    ferramentaNaMao = nullptr;
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramentaNaMao;
}

// --- Ações ---
void Jardineiro::aplicarFerramenta() {
    std::cout << "Usa a ferramenta nesta posicao" << std::endl;
}

void Jardineiro::resetTurno() {
    movimentosRestantes = 10;
    colheitasRestantes = 5;
    plantasRestantes = 2;
}

// Agora esta função pertence à classe Jardineiro (tem Jardineiro:: antes)
void Jardineiro::processarMovimento(Jardim* jardim) {
    if (jardim == nullptr) return;

    // --- 1. ATUALIZAÇÃO VISUAL (* no mapa) ---

    // Se já estavamos noutro sitio, removemos o boneco de lá
    if (this->localAtual != nullptr) {
        this->localAtual->removeJardineiro();
    }

    // Atualizamos o ponteiro 'localAtual' para a nova posição (linha, coluna)
    this->localAtual = jardim->getBocado(this->linha, this->coluna);

    // Colocamos o boneco no novo sitio
    if (this->localAtual != nullptr) {
        this->localAtual->colocaJardineiro();
    }

    // --- 2. APANHAR FERRAMENTAS ---

    // Tentar apanhar ferramenta do chão na posição atual
    Ferramenta* f = jardim->apanharFerramenta(this->linha, this->coluna);

    if (f != nullptr) {
        this->adicionarFerramenta(f);
        cout << ">> O Jardineiro encontrou um(a) " << f->mostra() << "!" << endl;
    }
}

void Jardineiro::entrar(Jardim* jardim, int l, int c) {
    if (jardim == nullptr) return;

    this->linha = l;
    this->coluna = c;
    this->dentroDoJardim = true;
    cout << "Jardineiro entrou na posicao " << l << " " << c << endl;

    processarMovimento(jardim);
}

void Jardineiro::cima(Jardim* jardim) {
    if (!dentroDoJardim || movimentosRestantes <= 0) return;

    if (this->linha > 0) {
        this->linha--;
        this->movimentosRestantes--;
        processarMovimento(jardim);
    }
}

void Jardineiro::baixo(Jardim* jardim) {
    if (!dentroDoJardim || movimentosRestantes <= 0) return;

    this->linha++;
    this->movimentosRestantes--;
    processarMovimento(jardim);
}

void Jardineiro::esquerda(Jardim* jardim) {
    if (!dentroDoJardim || movimentosRestantes <= 0) return;

    if (this->coluna > 0) {
        this->coluna--;
        this->movimentosRestantes--;
        processarMovimento(jardim);
    }
}

void Jardineiro::direita(Jardim* jardim) {
    if (!dentroDoJardim || movimentosRestantes <= 0) return;

    this->coluna++;
    this->movimentosRestantes--;
    processarMovimento(jardim);
}

// --- Informação ---
string Jardineiro::getInfo() const {
    string info = "Jardineiro ";
    info += (dentroDoJardim ? "está no jardim" : "está fora do jardim");
    return info;
}