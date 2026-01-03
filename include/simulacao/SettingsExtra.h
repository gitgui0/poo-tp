#ifndef TP_SETTINGSEXTRA_H
#define TP_SETTINGSEXTRA_H

class SettingsExtra {
    public:
    class AceleradorCrescimento {
    public:
        static const int capacidade = 5;
    };
    class Orquidea {
    public:
        static const int inicial_agua = 25;
        static const int inicial_nutrientes = 25;
        static const int perde_agua = 1;
        static const int absorve_agua = 2;
        static const int absorve_agua_fraca = 5;
        static const int absorve_nutrientes = 5;
        static const int retribuicao_nutrientes = 3;
        static const int instantes_morre = 10;
        static const int multiplica_agua_maior = 60;
        static const int multiplica_nutrientes_maior = 50;
        static const int agua_maior_perde = 80;
        static const int agua_menor_perde = 30;
        static const int agua_prejudicial_instantes = 5;

    };
};

#endif