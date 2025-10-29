
#include "Simulador.h"
#include "Comando.h"

#include <iostream>
#include <sstream>

using namespace std;

Simulador::Simulador(){
  cout << "construtor simulador" << endl;
  for(int i = 0; i < MAX_CMDS; i++){
    cmds[i] = nullptr;
  }
  nComandos = 0;
}; // por agora

bool Simulador::adicionaComando(Comando & cmd){
  for(int i = 0; i < MAX_CMDS;i++){
    if(cmds[i] == nullptr){
      cmds[i] = &cmd;
      nComandos++;
      return true;
    }
  }
  return false;
}

void Simulador::avancaInstante(){
  nInstantes++;
}

void Simulador::criaJardim(int nLinhas, int nColunas){
  jardim = Jardim(nLinhas,nColunas); //TODO: ISTO ANIDA NAO ESTA DEVIDAMENTE TESTADO
}
void Simulador::mostraInterface() const { cout << "placeholder para interface" << endl;} ;

Comando* Simulador::parse(const string &input, istringstream& parametros) {
  istringstream iss(input);
  string cmd;
  iss >> cmd;

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


bool Simulador::executa(const string &input){
  istringstream params;
  Comando* exec = parse(input,params);

  if(exec == nullptr) return false;

  return exec->executa(*this,params); // nao sei ainda se vou deixar em return
}
