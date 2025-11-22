
#include "Jardineiro.h"
#include <iostream>
#include "Settings.h"
using namespace std;

Jardineiro::Jardineiro() : ferramentaNaMao(nullptr),
                           movimentosRestantes(Settings::Jardineiro::max_movimentos), // 10
                           colheitasRestantes(Settings::Jardineiro::max_colheitas),   // 5
                           plantasRestantes(Settings::Jardineiro::max_plantacoes),     // 2
						   localAtual(nullptr),
                           dentroDoJardim(false){
    // O std::vector<Ferramenta*> ferramentas e inicializado automaticamente vazio

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