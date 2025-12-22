
#include "Simulador.h"
#include "Comando.h"
#include "ComandosTodos.h"
#include "Jardineiro.h"
#include "Planta.h"

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

Simulador::~Simulador() {
  // delete jardim; é unique_ptr
  delete jardineiro;
  delete interface;

  for (Comando* c : cmds) {
    delete c;
  }

  cmds.clear();

  salvos.clear();


}

void Simulador::avancaInstante(){
  nInstantes++;
  jardineiro->resetTurno();
  int n = jardim->getLinhas();
  int l = jardim->getColunas();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {

      bool plantaMorreu = false;

      BocadoSolo* b = jardim->getBocado(i,j);
      Planta* p = b->getPlanta();


      if (p)
        plantaMorreu = p->cadaInstante(b);

      if (plantaMorreu)
        b->setPlanta(nullptr);
      else {
        //logica extra para roseira, isto mais para nao ter que mandar o jardim a funcao
        // cadaInstante das plantas, ate porque nem todas existem
        if (p!=nullptr) {
          if (p->getLetra() == 'r') {
            BocadoSolo* boc = p->geraVizinho(b,jardim.get());

            // Ou seja, nao ha nenhum vizinho sem planta
            if (boc==nullptr)
              b->setPlanta(nullptr);
          }
        }

      }
    }
  }
}

void Simulador::criaJardim(int nLinhas, int nColunas) {
  // Validacoes ja estao no comando
  jardim = std::make_unique<Jardim>(nLinhas, nColunas);
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
      parametros.clear();
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


void Simulador::registaComandos() {

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

char Simulador::intParaChar(int n) {
  return n + 'A';
}

string Simulador::mostraJardim() const {
  if (jardim==nullptr)
      return "";

  ostringstream oss;
  oss << jardim->mostraJardim();
  return oss.str();

}


void Simulador::gravarJardim(const std::string& nome) {
  if (jardim == nullptr) {
    throw std::runtime_error("Nao existe nenhum jardim ativo para gravar.");
  }
  // deep copy para salvar
  salvos[nome] = jardim->clone();
}

void Simulador::recuperarJardim(const std::string& nome) {
  auto it = salvos.find(nome);
  if (it == salvos.end()) {
    throw std::runtime_error("Nao existe nenhum jardim salvo com esse nome.");
  }

  // Se ja existisse um jardim ativo, o unique_ptr destroi-o antes de receber o recuperado
  jardim = std::move(it->second);

  // Remove a copia no map. A copia ja nao tem o jardim mas mais pela memoria
  salvos.erase(it);

}

void Simulador::apagarJardim(const std::string& nome) {
  if (salvos.erase(nome) < 0) {
    throw std::runtime_error("Save nao encontrado para apagar.");
  }
}