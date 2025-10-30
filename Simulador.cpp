
#include "Simulador.h"
#include "Comando.h"
#include "ComandosTodos.h"
#include "Jardineiro.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Simulador::Simulador()
  : jardim(nullptr), nComandos(0), nInstantes(0)
{
  for (int i = 0; i < MAX_CMDS; i++)
    cmds[i] = nullptr;

  interface = new Interface(this);
  jardineiro = new Jardineiro();

  registaComandos();
}



void Simulador::avancaInstante(){
  nInstantes++;
}

void Simulador::criaJardim(int nLinhas, int nColunas) {
  // Validacoes ja estao no comando
  delete jardim;
  jardim = new Jardim(nLinhas, nColunas);
}

Comando* Simulador::parse(const string &input, istringstream& parametros) {
  istringstream iss(input);
  string cmd;
  iss >> cmd;
  if (cmd.empty()) throw 1; // nao pode ser 1

  for(int i = 0; i < nComandos; i++){
    if(cmds[i]->getNome() == cmd){
      string resto;
      getline(iss,resto);
      parametros.clear(); // so no caso
      parametros.str(resto);

      return cmds[i];
    }
  }

  return nullptr;

}


void Simulador::executa(const string &input){
  istringstream params;
  Comando* exec = parse(input,params);

  if(exec == nullptr) throw std::runtime_error("Esse comando nao foi encontrado");

  exec->executa(*this,params);

}


void Simulador::corre() {
  interface->inicia();
}

void Simulador::registaComandos() {
  cmds[nComandos++] = new ComandoAvanca();
  cmds[nComandos++] = new ComandoJardim();
  cmds[nComandos++] = new ComandoEntraJardim();
}

int Simulador::charParaInt(char c) {
  return toupper(c) - 'A';
}
