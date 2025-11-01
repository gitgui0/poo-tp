cmake_minimum_required(VERSION 3.30)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP
        # Núcleo e Interface
        main.cpp
        Simulador.cpp
        Interface.cpp

        # Domínio (Jardim, Solo e Jardineiro)
        Jardim.cpp
        BocadoSolo.cpp
        Jardineiro.cpp

        # Classes Base
        EstaSolo.cpp
        Planta.cpp
        Ferramenta.cpp

        # Classes de Plantas
        Cacto.cpp
        ErvaDaninha.cpp
        Roseira.cpp
        Orquidea.cpp

        # Classes de Ferramentas
        Adubo.cpp
        Regador.cpp
        TesouraPoda.cpp
        AceleradorCrescimento.cpp

        # Comandos
        Comando.cpp
        ComandosTodos.cpp
)
