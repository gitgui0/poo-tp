#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "EstaSolo.h"
#include <string>
#include <sstream>

class BocadoSolo;
class Jardim;

class Ferramenta : public EstaSolo {
    public:
        explicit Ferramenta(char letra);
        ~Ferramenta() override = 0;

        virtual bool aplica(BocadoSolo* b, Jardim* j) = 0;
        virtual std::string mostra() const = 0;
        virtual Ferramenta* clone() const = 0;

        int getNumSerie() const noexcept { return numSerie; }
        friend std::ostream& operator<<(std::ostream& os, const Ferramenta* f);
        static Ferramenta* criar(char ferr);

    private:
        static int seq;
        int numSerie;

};

#endif