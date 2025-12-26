
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
  : jardim(nullptr), nComandos(0)
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

  // comandos sao unique pointers

  cmds.clear();

  salvos.clear();

}

void Simulador::avancaInstante(){
  jardineiro->resetTurno();

  jardineiro->aplicarFerramenta(jardim.get());
  jardineiro->pegaFerramenta();

  jardim->setInstantes();
  jardim->processaTurno();
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


  for(const unique_ptr<Comando> &c : cmds){
    if(c->getNome() == cmd){
      string resto;
      getline(iss,resto);
      parametros.clear();
      parametros.str(resto);
      return c.get();
    }
  }
  return nullptr;
}


void Simulador::executa(const string &input){
  istringstream params;
  Comando* exec = parse(input,params);

  if(exec == nullptr)
      throw std::runtime_error("Esse comando nao foi encontrado");
  string n = exec->getNome();

  if (jardim == nullptr && exec->getNome() != "jardim")
      throw std::runtime_error("Nao existe jardim.");

  exec->executa(*this,params);

}


void Simulador::registaComandos() {

  cmds.push_back(make_unique<ComandoAvanca>());
  cmds.push_back(make_unique<ComandoJardim>());
  cmds.push_back(make_unique<ComandoEntraJardim>());

  cmds.push_back(make_unique<ComandoGrava>());
  cmds.push_back(make_unique<ComandoRecupera>());
  cmds.push_back(make_unique<ComandoApaga>());
  cmds.push_back(make_unique<ComandoExecuta>());

  cmds.push_back(make_unique<ComandoLPlantas>());
  cmds.push_back(make_unique<ComandoLPlanta>());
  cmds.push_back(make_unique<ComandoLArea>());
  cmds.push_back(make_unique<ComandoLSolo>());
  cmds.push_back(make_unique<ComandoLFerr>());

  cmds.push_back(make_unique<ComandoColhe>());
  cmds.push_back(make_unique<ComandoPlanta>());
  cmds.push_back(make_unique<ComandoLarga>());
  cmds.push_back(make_unique<ComandoPega>());
  cmds.push_back(make_unique<ComandoCompra>());

  cmds.push_back(make_unique<ComandoMoveEsquerda>());
  cmds.push_back(make_unique<ComandoMoveDireita>());
  cmds.push_back(make_unique<ComandoMoveCima>());
  cmds.push_back(make_unique<ComandoMoveBaixo>());
  cmds.push_back(make_unique<ComandoSai>());

  cmds.push_back(make_unique<ComandoFim>());

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


  /*
     Para casos em que o jardineiro estava dentro do jardim.
     Se o jardineiro estava num certo bocadosolo B, a cópia do jardim, tem esse bocadoSolo
    igual, ou seja, se depois usamos o recupera, esse B vai ter la o jardineiro. Mesmo
    que o jardineiro atual nao esteja la.

     É o que esta parte da função faz, se houver um bocadoSolo que foi guardado com o jardineiro la,
     "sincroniza" o jardineiro atual
  */
  jardineiro->mudaLocal(jardim->getBocadoDoJardineiro());
  jardineiro->setEstaDentro(jardineiro->getLocalAtual() == nullptr);

  // Remove a copia no map. A copia ja nao tem o jardim mas mais pela memoria
  salvos.erase(it);

}

void Simulador::apagarJardim(const std::string& nome) {
  if (salvos.erase(nome) < 0) {
    throw std::runtime_error("Save nao encontrado para apagar.");
  }
}


void Simulador::entraNoJardim(char l, char c) const {
  BocadoSolo *b = jardim->getBocado(charParaInt(l), charParaInt(c));

  jardineiro->move(b);
}


void Simulador::colherPlanta(char l, char c) {
  if (jardineiro->getColheitasRestantes() <= 0)
    throw std::runtime_error("Nao pode colher mais plantas neste turno");

  int linha = charParaInt(l), coluna = charParaInt(c);

  if (!jardim->colhe(linha,coluna)) {
    throw std::runtime_error("Nao existe planta nessa posicao");
  }

  jardineiro->menosColheitasRestantes();

}

void Simulador::planta(char l, char c, char planta) {
  if (jardineiro->getPlantasRestantes() <= 0)
    throw std::runtime_error("Nao pode plantar mais plantas neste turno");

  int linha = charParaInt(l), coluna = charParaInt(c);

  jardim->planta(linha,coluna,planta);
  jardineiro->menosPlantasRestantes();
}

void Simulador::moveJardineiro(int dirX, int dirY) const {
  BocadoSolo* b = jardineiro->getLocalAtual(), *novo;

  std::pair<int,int> posicao = jardim->getPosicaoBocado(b);
  int l = posicao.first;
  int c = posicao.second;

  novo = jardim->getBocado(l + dirY,c + dirX);
  if (novo==nullptr)
    throw std::runtime_error("O movimento nao e possivel.");

  jardineiro->move(novo);
}

void Simulador::saiDoJardim() const {
  jardineiro->sai();
}

void Simulador::compraEAdiciona(char ferr) {
  Ferramenta* novaFerramenta = Ferramenta::criar(ferr);
  jardineiro->adicionarFerramenta(novaFerramenta);
}

void Simulador::pegaFerramenta(int num) {
  jardineiro->pegaFerramenta(num);
}


void Simulador::corre() const {
  interface->setLigado(true);
  interface->inicia();
}

void Simulador::para() const {
  interface->setLigado(false);
}

