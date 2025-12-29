#include "AceleradorCrescimento.h"

#include <BocadoSolo.h>
#include <iostream>
#include <Planta.h>

#include "Settings.h"
#include "Settings.h"

using namespace std;

AceleradorCrescimento::AceleradorCrescimento() :
    Ferramenta('z'),
    capacidade(Settings::AceleradorCrescimento::capacidade)
{}

bool AceleradorCrescimento::aplica(BocadoSolo* b, Jardim* j) {

    Planta* p = b->getPlanta();
    if (p!=nullptr) {
        for (int i = 0 ; i < 3; i++) {
            bool plantaMorreu = p->cadaInstante(b,j);

            if (plantaMorreu) {
                b->setPlanta(nullptr);
                break;
            }

        }
        capacidade--;
    }

    return capacidade <= 0;
}

std::string AceleradorCrescimento::mostra() const {
    ostringstream oss;
    oss << getNumSerie() << " - Acelerador de Crescimento - Capacidade - " << capacidade << endl;
    return oss.str();
}
