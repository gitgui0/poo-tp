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
    this->agua = randomAgua(gen);
    this->nutrientes = randomNutri(gen);

    planta = nullptr;
    ferramenta = nullptr;
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



