#include "BocadoSolo.h"
#include "Settings.h"
#include <random>
#include "Planta.h"

BocadoSolo::BocadoSolo() : ocupado(false){
    std::random_device rd;
    std::mt19937 gen(rd());

    // Cria uma distribuição uniforme de inteiros
    std::uniform_int_distribution<int> randomAgua(Settings::Jardim::agua_min,Settings::Jardim::agua_max);
    std::uniform_int_distribution<int> randomNutri(Settings::Jardim::nutrientes_min,Settings::Jardim::nutrientes_max);

    // Gera um valor aleatório
    this->agua =  randomAgua(gen);
    this->nutrientes = randomNutri(gen);

    planta = nullptr;
    ferramenta = nullptr;
}

BocadoSolo& BocadoSolo::operator=(const BocadoSolo& outro) {
    if (this == &outro) {
        return *this;
    }

    // Dados simples
    this->agua = outro.agua;
    this->nutrientes = outro.nutrientes;
    this->ocupado = outro.ocupado;

    delete this->planta;
    delete this->ferramenta;

    // Deep copy da planta
    if (outro.planta != nullptr) {
        // O clone() garante que se for Cacto, cria um novo Cacto
        this->planta = outro.planta->clone();
    } else {
        this->planta = nullptr;
    }

    // Deep copy da ferramenta
    if (outro.ferramenta != nullptr) {
        this->ferramenta = outro.ferramenta->clone();
    } else {
        this->ferramenta = nullptr;
    }

    return *this;
}

// Nao é usado, foi criado mais para "no caso"
BocadoSolo::BocadoSolo(const BocadoSolo& other)
    : agua(other.agua), nutrientes(other.nutrientes), ocupado(other.ocupado), planta(nullptr), ferramenta(nullptr)
{
    if (other.planta != nullptr) {
        this->planta = other.planta->clone();
    }
    if (other.ferramenta != nullptr) {
        this->ferramenta = other.ferramenta->clone();
    }
}

//Devolve o ponteiro e limpa a variavel, mas nao liberta a memoria
Ferramenta* BocadoSolo::retiraFerramenta() {
    if (this->ferramenta == nullptr) {
        return nullptr;
    }

    Ferramenta* temp = this->ferramenta;

    this->ferramenta = nullptr;

    return temp;
}

BocadoSolo::~BocadoSolo() {
    delete planta;
    delete ferramenta;
}



char BocadoSolo::mostra() {
    if (estaJardineiro()) return '*';
    if (planta) return planta->getLetra();
    if (ferramenta) return ferramenta->getLetra();
    return ' ';
}

void BocadoSolo::setPlanta(Planta* p) {
    delete planta;
    planta = p;
}
void BocadoSolo::setFerramenta(Ferramenta* f) {
    delete ferramenta;
    ferramenta = f;
}

bool BocadoSolo::setAgua(int agua) {
    if (agua<0) return false;
    this->agua = agua;
    return true;
}
bool BocadoSolo::setNutrientes(int nutrientes) {
    if (nutrientes<0) return false;
    this->nutrientes = nutrientes;
    return true;
}
