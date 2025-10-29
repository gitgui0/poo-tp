#include "Interface.h"

using namespace std;

Interface::Interface() {}

Interface::~Interface() {
    //delete jardim????
}

void Interface::inicia() {
    string linha;

    cout << "===== Trabalho Ip =====" << endl;
    cout << "Comandos disponiveis: jardim <linhas> <colunas> | mostra | fim" << endl;

    while (running) {
        cout << "\n";
        getline(cin, linha);

        if (linha.empty()) continue;

        processaComando(linha);
    }
}

void Interface::processaComando(const string & linha) {
    string partes[4]; // isto tá ate 4 palavras mas se depois for preciso mais
                      // mas isto depois vê-se
    int numPartes = separaPalavras(linha,partes,4);
    if (numPartes == 0) return; //so para se deres enter sem nada, podes cagar nisto se quiseres

    string comando = partes[0];

    if (comando == "fim") {
        running = false;
        cout << "Acabou se a festa chavalos" << endl;
    }
    else if (comando == "jardim") { //meti jardim mas e so pa testar pode ser mostra ou o que quiseres
        if (numPartes < 3) {
            cout << "Tens que inserir: jardim <linhas> <colunas>" << endl;
            //so pa verificar se nao pos tipo jardim 2
            return;
        }
        int linhas = stoi(partes[1]);
        int colunas = stoi(partes[2]);

        cout << "[TESTE] O jardim vai ser "<< linhas <<  "x" << colunas << endl;
    }
    else if (comando == "mostra") {
        mostraJardim();
    }
    else {
        cout << "nao existe" << endl;
    }
}

//fui buscar esta full ao jorge por agora foi só pa testar, mas até dá para deixar
//só usa é umas cenas meio questionaveis
int Interface::separaPalavras(const string& linha, string partes[], int maxPartes) const {
    int count = 0;
    string atual;

    for (char c : linha) {
        if (isspace(c)) {
            if (!atual.empty()) {
                if (count < maxPartes)
                    partes[count++] = atual;
                atual.clear();
            }
        } else {
            atual += c;
        }
    }

    if (!atual.empty() && count < maxPartes)
        partes[count++] = atual;

    return count;
}

void Interface::mostraJardim() const {

}