#ifndef ESTASOLO_H
#define ESTASOLO_H

class EstaSolo {
    public:
        explicit EstaSolo(char letra);
        char getLetra() const noexcept { return letra;};
        virtual ~EstaSolo() = 0;

    private:
        char letra;

};

#endif
