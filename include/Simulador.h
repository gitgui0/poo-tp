
#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include "Interface.h"
#include <sstream>
#include <vector>

// ************** IMPORTANTE *********************
// em vez do include, para nao haver um loop de includes
class Comando;

class Simulador {

  public:
    Simulador();
    ~Simulador();
    void avancaInstante();
    int getInstantes() const noexcept { return nInstantes; }

    Interface* devolveInterface(){return interface;}

    void criaJardim(int nLinhas, int nColunas);
    string mostraJardim() const;


    const Jardim * devolveJardim() const { return jardim; }
    Jardim * devolveJardim() { return jardim; }

    const Jardineiro * devolveJardineiro() const { return jardineiro; }
    Jardineiro * devolveJardineiro() { return jardineiro; }

    Comando* parse(const std::string &input, std::istringstream& parametros);
    void executa(const std::string &input);

    static int charParaInt(char c);
    static char intParaChar(int n);

  private:
    void registaComandos();


    Jardim* jardim;
    Jardineiro* jardineiro;

    std::vector<Comando*> cmds;
    int nInstantes;
    int nComandos;

    Interface* interface;

};



#endif
