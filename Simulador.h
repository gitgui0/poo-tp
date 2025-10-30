
#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include "Interface.h"
#include <sstream>

// ************** IMPORTANTE *********************
// em vez do include, para nao haver um loop de includes
class Comando;

class Simulador {

  public:
    Simulador();

    bool adicionaComando(Comando & cmd);

    void avancaInstante();
    int getInstantes() const noexcept { return nInstantes; }

    void criaJardim(int nLinhas, int nColunas);
    void mostraInterface() const ;
    void corre();

    const Jardim * devolveJardim() const { return jardim; }

    Comando* parse(const std::string &input, std::istringstream& parametros);
    bool executa(const std::string &input);

  private:
    static const int MAX_CMDS = 30;

    Jardim* jardim;
    Jardineiro jardineiro;

    Comando *cmds[MAX_CMDS];

    int nInstantes;
    int nComandos;

    Interface* interface;

};



#endif
