#include "Interface.h"
#include "Simulador.h"
#include <iostream>

using namespace std;

Interface::Interface(Simulador * sim) : sim(sim), ligado(true) {}

Interface::~Interface() = default;

void Interface::inicia() {
    string linha;

    cout << "===== POO TP 25/26 | SIMULADOR JARDIM =====" << endl;

    while (ligado) {
        mostraJardim();
        cout << "\n>";
        getline(cin, linha);

        if (linha.empty()) continue;
        if (linha=="fim") {
            ligado = false;
            break;
        }

        try {
            sim->executa(linha);
            if (sim->devolveJardineiro()->estaDentro()) {
                Jardim* jar = sim->devolveJardim();
                Jardineiro* j = sim->devolveJardineiro();
                BocadoSolo* b = j->getLocalAtual();

                Ferramenta*f = jar->apanharFerramenta(b);
                if (f!=nullptr) {
                    j->adicionarFerramenta(f); // adicionar ao inventario do jardineiro
                }
            }
        } catch (const exception &e) {
            cout << "Erro: " << e.what() << endl;
        } catch (...) {
            // captura outras excecoes
            cout << "Erro ao executar: " << linha << endl;
        }
    }
}

void Interface::mostraJardim() const {
    if (sim->devolveJardim() != nullptr) {
        cout << "\n";
        const Jardim* j= sim->devolveJardim();
        cout << j->mostraJardim();
    }
}