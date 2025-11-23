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
                           dentroDoJardim(false)
{
}

Jardineiro::~Jardineiro() = default;

// --- Ferramentas ---
void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f!=nullptr) ferramentas.push_back(f);
}

void Jardineiro::pegaFerramenta(Ferramenta* f) {
    if (f==nullptr) return; //TODO: MENSAGEM DE JEITO PARA METER NO THROW
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

// --- Informação ---
string Jardineiro::getInfo() const {
    string info = "Jardineiro ";
    info += (dentroDoJardim ? "está no jardim" : "está fora do jardim");
    return info;
}