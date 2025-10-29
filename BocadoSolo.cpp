#include "BocadoSolo.h"
#include "Settings.h"
#include <iostream>
#include <random>

BocadoSolo::BocadoSolo() : ocupado(false){
  //este codigo ta duvidoso
    std::random_device rd;
    std::mt19937 gen(rd());

    // Cria uma distribuição uniforme de inteiros
    std::uniform_int_distribution<int> randomAgua(Settings::Jardim::agua_min,Settings::Jardim::agua_max);
    std::uniform_int_distribution<int> randomNutri(Settings::Jardim::nutrientes_min,Settings::Jardim::nutrientes_max);

    // Gera um valor aleatório
    this->agua = randomAgua(gen);
    this->nutrientes = randomNutri(gen);
}

int BocadoSolo::getAgua() const noexcept{ return agua;}
int BocadoSolo::getNutrientes() const noexcept {return nutrientes;}

bool BocadoSolo::estaJardineiro() const noexcept { return ocupado; }

void BocadoSolo::colocaJardineiro(){ ocupado = true; }
void BocadoSolo::removeJardineiro(){ ocupado = false; }