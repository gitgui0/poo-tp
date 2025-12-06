#include "AceleradorCrescimento.h"

#include <BocadoSolo.h>
#include <iostream>
#include <Planta.h>

using namespace std;

AceleradorCrescimento::AceleradorCrescimento() :
    Ferramenta('z'),
    capacidade(5)
{}

AceleradorCrescimento::~AceleradorCrescimento() = default;

bool AceleradorCrescimento::aplica(BocadoSolo* b, Jardim* j) {

    Planta* p = b->getPlanta();
    if (p!=nullptr) {
        for (int i = 0 ; i < 3; i++) {
            bool plantaMorreu = p->cadaInstante(b);

            if (plantaMorreu)
                b->setPlanta(nullptr);
            else {
                if (p->getLetra() == 'r') {
                    BocadoSolo* b = p->geraVizinho(b,j);

                    // Ou seja, nao ha nenhum vizinho sem planta
                    if (b==nullptr)
                        b->setPlanta(nullptr);
                }
            }
        }
        capacidade--;
    }

    return capacidade <= 0;
}

std::string AceleradorCrescimento::mostra() const {
    ostringstream oss;
    oss << "Acelerador de Crescimento -" << getNumSerie() <<  "\nCapacidade: " << capacidade << endl;
    return oss.str();
}
