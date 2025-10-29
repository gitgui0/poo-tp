
#ifndef TP_INTERFACE_H
#define TP_INTERFACE_H

#include <string>
#include <iostream>

using namespace std;

//so ta aqui pa testar ignora só
class Jardim;

class Interface {
private:
    //tirei do jorge mas percebi o que faz e pq, avisa qqlr mrd sfv
    Jardim* jardim = nullptr; //acho que assim nao fica mau, mas fala comigo se achas que ponteiro aqui é estupido
                              //basicamente aponta para o jardim que está associado, tipo o comando
                              //está a mexer neste jardim mas isto é pa adaptares quando fores fazer
                              //a classe jardim
    bool running = true;

    void processaComando(const string& linha);
    int separaPalavras(const string& linha, string partes[], int maxPartes) const;
    // esta funcao basicamente e tipo se metes "jardim 12 6" separar e criar um jardim 12 por 6


public:
    Interface();
    ~Interface();
    void inicia(); //isto é tipo pa criar o loop principal
    void mostraJardim() const; //facil de entender o que faz, mas meti porque nao temos
                                //muita nocao como vai ser
};


#endif //TP_INTERFACE_H