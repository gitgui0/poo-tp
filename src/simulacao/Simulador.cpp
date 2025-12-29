
#include "Simulador.h"
#include "Comando.h"
#include "ComandosTodos.h"
#include "Jardineiro.h"
#include "Planta.h"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

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
    if (jardineiro->estaDentro()) {
        jardineiro->aplicarFerramenta(jardim.get());
        jardineiro->pegaFerramenta(jardim.get());
    }
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

  if (jardim == nullptr)
      if ( !(exec->getNome() == "jardim" || exec->getNome() == "executa") )
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
  jardineiro->setEstaDentro(jardineiro->getLocalAtual() != nullptr);

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
    jardineiro->pegaFerramenta(jardim.get());
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
    jardineiro->pegaFerramenta(jardim.get());

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


string Simulador::listaPlantas() const {
    if (jardim == nullptr) throw runtime_error("O jardim nao existe.");

    ostringstream oss;
    bool encontrou = false;
    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {
            BocadoSolo* b = jardim->getBocado(i, j);
            if (b == nullptr) continue;

            Planta* p = b->getPlanta();

            if (p != nullptr) {
                encontrou = true;
                string nomePlanta;
                char l = p->getLetra();

                // Switch simples para nomes bonitos
                if (l == 'c') nomePlanta = "Cacto";
                else if (l == 'e') nomePlanta = "Erva Daninha";
                else if (l == 'x') nomePlanta = "Orquidea";
                else if (l == 'r') nomePlanta = "Roseira";
                else nomePlanta = "Planta Desconhecida";

                oss << "Planta: " << nomePlanta << " [" << intParaChar(i) << intParaChar(j) << "]\n";
                oss << "   Vida -> Agua: " << p->obterAgua() << " | Nutrientes: " << p->obterNutrientes() << "\n";
                oss << "   Solo -> Agua: " << b->getAgua() << " | Nutrientes: " << b->getNutrientes() << "\n\n";
            }
        }
    }
    if (!encontrou) oss << "Nao existem plantas no jardim.\n";

    // Adicionar visualizacao do jardim no fim, conforme pedido implicito em alguns enunciados
    oss << "--- Mapa Atual ---\n" << mostraJardim();

    return oss.str();
}

string Simulador::listaPlanta(char l, char c) const {
    if (jardim == nullptr) throw runtime_error("O jardim nao existe.");

    int li = charParaInt(l);
    int ci = charParaInt(c);
    BocadoSolo* b = jardim->getBocado(li, ci);

    if (b == nullptr) throw runtime_error("Posicao invalida.");

    Planta* p = b->getPlanta();
    ostringstream oss;

    if (p == nullptr) {
        oss << "Nao existe planta na posicao " << l << c << "\n";
        oss << "Info Solo -> Agua: " << b->getAgua() << " | Nutrientes: " << b->getNutrientes() << "\n";
    } else {
        oss << "--- Detalhes " << l << c << " ---\n";
        oss << "Planta: " << p->getLetra() << " (" << p->getBeleza() << ")\n";
        oss << "   Estado Planta -> Agua: " << p->obterAgua() << " | Nutrientes: " << p->obterNutrientes() << "\n";
        oss << "   Estado Solo   -> Agua: " << b->getAgua() << " | Nutrientes: " << b->getNutrientes() << "\n";
    }
    return oss.str();
}

string Simulador::listaArea() const {
    if (jardim == nullptr) throw runtime_error("O jardim nao existe.");

    ostringstream oss;
    oss << "--- Area Ocupada ---\n";
    bool encontrouAlgo = false;

    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {
            BocadoSolo* b = jardim->getBocado(i, j);
            // Se tiver qualquer coisa (Planta, Ferramenta ou Jardineiro)
            if (b->getPlanta() != nullptr || b->getFerramenta() != nullptr || b->estaJardineiro()) {
                encontrouAlgo = true;
                oss << "[" << intParaChar(i) << intParaChar(j) << "] ";

                if (b->estaJardineiro()) oss << "<JARDINEIRO> ";
                if (b->getPlanta()) oss << "Planta(" << b->getPlanta()->getLetra() << ") ";
                if (b->getFerramenta()) oss << "Ferr(" << b->getFerramenta()->getLetra() << ") ";

                oss << "| Solo(A:" << b->getAgua() << " N:" << b->getNutrientes() << ")\n";
            }
        }
    }
    if (!encontrouAlgo) oss << "Tudo vazio.\n";
    return oss.str();
}

string Simulador::listaSolo(char l, char c, int raio) const {
    if (jardim == nullptr) throw runtime_error("O jardim nao existe.");

    int centroL = charParaInt(l);
    int centroC = charParaInt(c);
    if (jardim->getBocado(centroL, centroC) == nullptr) throw runtime_error("Posicao central invalida.");

    ostringstream oss;
    oss << "--- Info Solo (Centro: " << l << c << " | Raio: " << raio << ") ---\n";

    // Calcular limites garantindo que nao sai da matriz (std::max e std::min)
    int inicioL = std::max(0, centroL - raio);
    int fimL = std::min(jardim->getLinhas() - 1, centroL + raio);
    int inicioC = std::max(0, centroC - raio);
    int fimC = std::min(jardim->getColunas() - 1, centroC + raio);

    for (int i = inicioL; i <= fimL; i++) {
        for (int j = inicioC; j <= fimC; j++) {
            BocadoSolo* b = jardim->getBocado(i, j);
            oss << "> " << intParaChar(i) << intParaChar(j)
                << " | A:" << b->getAgua() << " N:" << b->getNutrientes();

            if (b->estaJardineiro()) oss << " [Jardineiro]";
            if (b->getPlanta()) oss << " [" << b->getPlanta()->getLetra() << "]";
            if (b->getFerramenta()) oss << " [" << b->getFerramenta()->getLetra() << "]";
            oss << "\n";
        }
    }
    return oss.str();
}

string Simulador::listaFerramentas() const {
    ostringstream oss;

    // Ferramenta na mao
    Ferramenta* naMao = jardineiro->getFerramentaNaMao();
    if (naMao != nullptr) {
        oss << "NA MAO: " << naMao->mostra();
    } else {
        oss << "NA MAO: Nenhuma\n";
    }

    // Ferramentas na mochila
    vector<Ferramenta*> mochila = jardineiro->devolveFerramentas();
    if (mochila.empty()) {
        oss << "MOCHILA: Vazia\n";
    } else {
        oss << "MOCHILA:\n";
        for (Ferramenta* f : mochila) {
            if (f != nullptr) {
                oss << "-> " << f->mostra();
            }
        }
    }
    return oss.str();
}