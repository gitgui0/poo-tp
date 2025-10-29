
#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Comando.h"
#include "Jardineiro.h"
#include <sstream>


class Simulador {

  public:
    Simulador();

    bool adicionaComando(Comando & cmd);

    void avancaInstante();
    int getInstantes() const noexcept { return nInstantes; }

    void criaJardim(int nLinhas, int nColunas);
    void mostraInterface() const ;

    Comando* parse(const std::string &input, std::istringstream& parametros);
    bool executa(const std::string &input);

  private:
    static const int MAX_CMDS = 30;

    Jardim jardim;
    Jardineiro jardineiro;

    Comando *cmds[MAX_CMDS];

    int nInstantes;
    int nComandos;

    //TODO: Interface interface;

};



#endif
