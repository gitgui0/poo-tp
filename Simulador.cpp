
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
  //vecotr inicializa a null diretamente
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
  if (cmd.empty()) throw std::runtime_error("Esse comando nao foi encontrado");

  for(Comando* c : cmds){
    if(c->getNome() == cmd){
      string resto;
      getline(iss,resto);
      parametros.clear(); // so no caso
      parametros.str(resto);
      return c;
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
  // Adicionar comandos usando push_back()
  cmds.push_back(new ComandoAvanca());
  cmds.push_back(new ComandoJardim());
  cmds.push_back(new ComandoEntraJardim());

  cmds.push_back(new ComandoGrava());
  cmds.push_back(new ComandoRecupera());
  cmds.push_back(new ComandoApaga());
  cmds.push_back(new ComandoExecuta());

  cmds.push_back(new ComandoLPlantas());
  cmds.push_back(new ComandoLPlanta());
  cmds.push_back(new ComandoLArea());
  cmds.push_back(new ComandoLSolo());
  cmds.push_back(new ComandoLFerr());

  cmds.push_back(new ComandoColhe());
  cmds.push_back(new ComandoPlanta());
  cmds.push_back(new ComandoLarga());
  cmds.push_back(new ComandoPega());
  cmds.push_back(new ComandoCompra());

  cmds.push_back(new ComandoMoveEsquerda());
  cmds.push_back(new ComandoMoveDireita());
  cmds.push_back(new ComandoMoveCima());
  cmds.push_back(new ComandoMoveBaixo());
  cmds.push_back(new ComandoSai());

  cmds.push_back(new ComandoFim());
}

int Simulador::charParaInt(char c) {
  return toupper(c) - 'A';
}
