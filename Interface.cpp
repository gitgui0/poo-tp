#include "Interface.h"

using namespace std;

Interface::Interface(Simulador * sim) : running(true) {
    this->sim = sim;
}

Interface::~Interface() {
    //delete jardim????
}

void Interface::inicia() {
    string linha;

    cout << "===== POO TP 25/26 =====" << endl;

    while (running) {
        mostraJardim();
        cout << "\n>";
        getline(cin, linha);

        if (linha.empty()) continue;
        if (linha=="fim") {
            // POR AGORA
            running = false;
            break;
        }

        if (!sim->executa(linha))
            cout << "Erro ao executar: " << linha << endl;
    }
}

void Interface::mostraJardim() const {
    if (sim->devolveJardim() != nullptr) {
        cout << "\n";
        cout << sim->devolveJardim()->mostraJardim();
    }
}