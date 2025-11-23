#ifndef COMANDOSTODOS_H
#define COMANDOSTODOS_H

#include "Comando.h"

// Comandos de Tempo
class ComandoAvanca : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    // Removi o 'const' depois de getNome()
    const char* getNome() override { return "avanca"; }
};

// Comandos de Gestão do Jardim
class ComandoJardim : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "jardim"; }
};

class ComandoEntraJardim : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "entra"; }
};

class ComandoGrava : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "grava"; }
};

class ComandoRecupera : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "recupera"; }
};

class ComandoApaga : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "apaga"; }
};

class ComandoExecuta : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "executa"; }
};

// Comandos de Informação (Listagens)
class ComandoLPlantas : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "lplantas"; }
};

class ComandoLPlanta : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "lplanta"; }
};

class ComandoLArea : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "larea"; }
};

class ComandoLSolo : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "lsolo"; }
};

class ComandoLFerr : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "lferr"; }
};

// Comandos de Ação
class ComandoColhe : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "colhe"; }
};

class ComandoPlanta : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "planta"; }
};

class ComandoLarga : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "larga"; }
};

class ComandoPega : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "pega"; }
};

class ComandoCompra : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "compra"; }
};

// Comandos de Movimento
class ComandoMoveEsquerda : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "e"; }
};

class ComandoMoveDireita : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "d"; }
};

class ComandoMoveCima : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "c"; }
};

class ComandoMoveBaixo : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "b"; }
};

class ComandoSai : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "sai"; }
};

class ComandoFim : public Comando {
public:
    void executa(Simulador &sim, std::istringstream &params) const override;
    const char* getNome() override { return "fim"; }
};

#endif // COMANDOSTODOS_H