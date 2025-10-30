
#include "Jardineiro.h"
#include <iostream>

using namespace std;

Jardineiro::Jardineiro() = default;
Jardineiro::~Jardineiro() = default;

bool Jardineiro::estaDentro() const {
    return dentroDoJardim;
}

BocadoSolo* Jardineiro::getLocalAtual() const {
    return localAtual;
}

void Jardineiro::entrarNoJardim(BocadoSolo* novoLocal) {
    // TODO: Validar se pode entrar e definir posição inicial
}

void Jardineiro::sairDoJardim() {
    // TODO: Implementar saída do jardim
}

//finge que esta nao ta aqui depende bue de como vais fazer os comandos
//void Jardineiro::mover(const string& direcao) {
    // TODO: Implementar movimentação (cima, baixo, esquerda, direita)
//}

// --- Ferramentas ---
void Jardineiro::adicionarFerramenta(unique_ptr<Ferramenta> f) {
    // TODO: Adicionar ao inventário
}

void Jardineiro::pegarFerramenta(int numeroSerie) {
    // TODO: Escolher ferramenta ativa
}

void Jardineiro::largarFerramenta() {
    // TODO: Largar ferramenta ativa
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramentaNaMao;
}

// --- Ações ---
void Jardineiro::aplicarFerramenta() {
    // TODO: Aplicar efeito da ferramenta atual na posição atual
}

void Jardineiro::resetTurno() {
    movimentosRestantes = 10;
    colheitasRestantes = 5;
    plantasRestantes = 2;
    podeEntrarSair = true;
}

// --- Informação ---
string Jardineiro::getInfo() const {
    // TODO: Retornar informação detalhada do jardineiro
    string info = "Jardineiro ";
    info += (dentroDoJardim ? "está no jardim" : "está fora do jardim");
    return info;
}