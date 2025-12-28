#ifndef COMANDOSTODOS_H
#define COMANDOSTODOS_H

#include "Comando.h"

class ComandoAvanca : public Comando {
public:
    ComandoAvanca() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "avanca"; }
};

class ComandoJardim : public Comando {
public:
    ComandoJardim() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "jardim"; }
};

class ComandoGrava : public Comando {
public:
    ComandoGrava() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "grava"; }
};

class ComandoRecupera : public Comando {
public:
    ComandoRecupera() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "recupera"; }
};

class ComandoApaga : public Comando {
public:
    ComandoApaga() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "apaga"; }
};

class ComandoExecuta : public Comando {
public:
    ComandoExecuta() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "executa"; }
};

class ComandoLPlantas : public Comando {
public:
    ComandoLPlantas() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "lplantas"; }
};

class ComandoLPlanta : public Comando {
public:
    ComandoLPlanta() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "lplanta"; }
};

class ComandoLArea : public Comando {
public:
    ComandoLArea() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "larea"; }
};

class ComandoLSolo : public Comando {
public:
    ComandoLSolo() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "lsolo"; }
};

class ComandoLFerr : public Comando {
public:
    ComandoLFerr() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "lferr"; }
};


class ComandoColhe : public Comando {
public:
    ComandoColhe() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "colhe"; }
};

class ComandoPlanta : public Comando {
public:
    ComandoPlanta() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "planta"; }
};

class ComandoLarga : public Comando {
public:
    ComandoLarga() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "larga"; }
};

class ComandoPega : public Comando {
public:
    ComandoPega() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "pega"; }
};

class ComandoCompra : public Comando {
public:
    ComandoCompra() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "compra"; }
};


class ComandoMoveEsquerda : public Comando {
public:
    ComandoMoveEsquerda() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "e"; }
};

class ComandoMoveDireita : public Comando {
public:
    ComandoMoveDireita() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "d"; }
};

class ComandoMoveCima : public Comando {
public:
    ComandoMoveCima() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "c"; }
};

class ComandoMoveBaixo : public Comando {
public:
    ComandoMoveBaixo() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "b"; }
};

class ComandoEntraJardim : public Comando {
public:
    ComandoEntraJardim() = default;
    void executa(Simulador & sim, std::istringstream & params) const override;
    const string getNome() override { return "entra"; }
};

class ComandoSai : public Comando {
public:
    ComandoSai() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "sai"; }
};

class ComandoFim : public Comando {
public:
    ComandoFim() = default;
    void executa(Simulador &sim, std::istringstream & params) const override;
    const string getNome() override { return "fim"; }
};

#endif
