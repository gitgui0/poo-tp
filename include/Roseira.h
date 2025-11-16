#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"

class Roseira : public Planta{
    public:
        void cadaInstante() override;

        Roseira();
        ~Roseira();
};



#endif
