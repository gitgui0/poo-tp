
#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include "Interface.h"
#include <vector>
#include <map>
#include <memory>

// em vez do include, para nao haver um loop de includes
class Comando;

class Simulador {

    public:
        Simulador();
        ~Simulador();

        void avancaInstante();
        void corre() const;
        void para() const;

        void criaJardim(int nLinhas, int nColunas);
        string mostraJardim() const;

        const Jardim * devolveJardim() const { return jardim.get(); }
        Jardim * devolveJardim() { return jardim.get(); }

        const Jardineiro * devolveJardineiro() const { return jardineiro; }
        Jardineiro * devolveJardineiro() { return jardineiro; }

        void colherPlanta(char l, char c);
        void planta(char l, char c, char planta);

        void entraNoJardim(char l, char c) const;
        void moveJardineiro(int dirX, int dirY) const;
        void saiDoJardim() const;

        string listaPlantas() const;
        string listaPlanta(char l, char c) const;
        string listaArea() const;
        string listaSolo(char l, char c, int raio) const;
        string listaFerramentas() const;

        void gravarJardim(const std::string& nome);
        void recuperarJardim(const std::string& nome);
        void apagarJardim(const std::string& nome);

        void compraEAdiciona(char ferr);
        void pegaFerramenta(int num);

        Comando* parse(const std::string &input, std::istringstream& parametros);
        void executa(const std::string &input);

    private:
        static int charParaInt(char c);
        static char intParaChar(int n);

        void registaComandos();

        std::unique_ptr<Jardim> jardim;
        Jardineiro* jardineiro;

        std::vector<unique_ptr<Comando>> cmds;
        int nComandos;

        Interface* interface;
        std::map<string, pair<unique_ptr<Jardim>,Jardineiro*>> salvos;
};



#endif
