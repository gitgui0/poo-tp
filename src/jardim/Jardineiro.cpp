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
                           entradasSaidasRestantes(Settings::Jardineiro::max_entradas_saidas),
                           localAtual(nullptr),
                           dentroDoJardim(false)
{
}

Jardineiro::~Jardineiro() {
    delete ferramentaNaMao;

    for (Ferramenta* f : ferramentas) {
        delete f;
    }
    ferramentas.clear();

}

// --- Ferramentas ---
void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f!=nullptr) ferramentas.push_back(f);
}


void Jardineiro::pegaFerramenta(int num) {
    largaFerramenta();
    Ferramenta* f;

    for (auto it = ferramentas.begin(); it != ferramentas.end(); ++it) {
        f = *it;
        if (f->getNumSerie() == num) {
            ferramentas.erase(it); // Remove do vetor, mas NÃO apaga o objeto da memória
            ferramentaNaMao = f;
            break;
        }
    }

    // Nao encontrou a ferramenta
    if (ferramentaNaMao == nullptr)
        throw std::runtime_error("Essa ferramenta nao esta no inventario");
}

void Jardineiro::pegaFerramenta(Jardim* j) {
    Ferramenta* f = j->apanharFerramenta(localAtual);

    if (f != nullptr) {
        adicionarFerramenta(f);
    }
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
void Jardineiro::aplicarFerramenta(Jardim* j) {
    bool acabou = false;
    if (ferramentaNaMao == nullptr)
        return;
    acabou = ferramentaNaMao->aplica(localAtual,j);
    std::cout << ferramentaNaMao << "foi aplicada" << endl;
    if (acabou){
        std::cout << ferramentaNaMao << "acabou." << endl;
        delete ferramentaNaMao;
        ferramentaNaMao = nullptr;
    }
}

void Jardineiro::resetTurno() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
    plantasRestantes = Settings::Jardineiro::max_plantacoes;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
}

// --- Informação ---
string Jardineiro::getInfo() const {
    string info = "Jardineiro ";
    info += (dentroDoJardim ? "está no jardim" : "está fora do jardim");
    return info;
}

void Jardineiro::move(BocadoSolo* b) {
    if (dentroDoJardim && localAtual != nullptr) {
        if (movimentosRestantes <= 0)
            throw std::runtime_error("O jardineiro nao se pode mover mais este turno.");

        movimentosRestantes--;
        localAtual->removeJardineiro();

    }else {
        if (entradasSaidasRestantes <= 0)
            throw std::runtime_error("O jardineiro nao se pode mover mais este turno.");

        entradasSaidasRestantes--;
    }

    localAtual = b;
    b->colocaJardineiro();
    dentroDoJardim = true;
}

void Jardineiro::sai() {
    if (entradasSaidasRestantes <= 0)
        throw std::runtime_error("O jardineiro ja nao pode sair. Tem que avancar o turno");

    if (localAtual!=nullptr) {
        localAtual->removeJardineiro();
        entradasSaidasRestantes--;
    }

    localAtual = nullptr;
    dentroDoJardim=false;
}


