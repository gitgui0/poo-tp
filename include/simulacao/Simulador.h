
#ifndef SIMULADOR_H
#define SIMULADOR_H


#include "Jardim.h"
#include "Jardineiro.h"
#include "Interface.h"
#include <sstream>
#include <vector>
#include <map>
#include <memory>

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


    const Jardim * devolveJardim() const { return jardim.get(); }
    Jardim * devolveJardim() { return jardim.get(); }

    const Jardineiro * devolveJardineiro() const { return jardineiro; }
    Jardineiro * devolveJardineiro() { return jardineiro; }

    Comando* parse(const std::string &input, std::istringstream& parametros);
    void executa(const std::string &input);

    static int charParaInt(char c);
    static char intParaChar(int n);

    void gravarJardim(const std::string& nome);
    void recuperarJardim(const std::string& nome);
    void apagarJardim(const std::string& nome);

  private:
    void registaComandos();

    std::unique_ptr<Jardim> jardim;
    Jardineiro* jardineiro;

    std::vector<Comando*> cmds;
    int nInstantes;
    int nComandos;

    Interface* interface;
    std::map<string, unique_ptr<Jardim>> salvos;
};



#endif
