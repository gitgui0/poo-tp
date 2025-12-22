#ifndef ESTASOLO_H
#define ESTASOLO_H

class EstaSolo {
    public:
      explicit EstaSolo(char letra);
      char getLetra() const noexcept;
      virtual ~EstaSolo() = 0; // virtual, porque por exemplo, as platnas sao destruidas de maneira diferente das ferramentas

    private:
      char letra;

};

#endif
