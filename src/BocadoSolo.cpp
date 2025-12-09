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

//isto é pa devolver o ponteiro e limpar a variavel
Ferramenta* BocadoSolo::retiraFerramenta() {
    if (this->ferramenta == nullptr) {
        return nullptr;
    }

    // Guarda ponteiro temporário
    Ferramenta* temp = this->ferramenta;

    // Esvazia o solo
    this->ferramenta = nullptr;

    return temp;
}

BocadoSolo::~BocadoSolo() {
    // Destroi a planta e a ferramenta se existirem
    delete planta;
    delete ferramenta;
}

int BocadoSolo::getAgua() const noexcept{ return agua;}
int BocadoSolo::getNutrientes() const noexcept {return nutrientes;}

bool BocadoSolo::estaJardineiro() const noexcept { return ocupado; }

void BocadoSolo::colocaJardineiro(){ ocupado = true; }
void BocadoSolo::removeJardineiro(){ ocupado = false; }

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
