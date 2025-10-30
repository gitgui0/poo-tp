#include "Interface.h"

#include "Simulador.h"

using namespace std;

Interface::Interface(Simulador * sim) : sim(sim), ligado(true) {}

Interface::~Interface() {
    //delete jardim????
}

void Interface::inicia() {
    string linha;

    cout << "===== POO TP 25/26 | SIMULADOR JARDIM =====" << endl;

    while (ligado) {
        mostraJardim();
        cout << "\n>";
        getline(cin, linha);

        if (linha.empty()) continue;
        if (linha=="fim") {
            // POR AGORA
            ligado = false;
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