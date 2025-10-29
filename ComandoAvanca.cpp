
#include "ComandoAvanca.h"
#include <iostream>
#include <string>

bool ComandoAvanca::executa(Simulador &sim, std::istringstream & params) const{
  int n;
  if (!(params >> n)) { //tenta ler dos params, se nao, fica com o default
    n = 1;
  }
  std::cout << "comando avanca com n=" << std::to_string(n) << std::endl;
  return true;
}