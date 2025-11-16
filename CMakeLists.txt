cmake_minimum_required(VERSION 3.30)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP
        # Núcleo e Interface
        main.cpp
        src/Simulador.cpp
        src/Interface.cpp

        # Domínio (Jardim, Solo e Jardineiro)
        src/Jardim.cpp
        src/BocadoSolo.cpp
        src/Jardineiro.cpp

        # Classes Base
        src/EstaSolo.cpp
        src/Planta.cpp
        src/Ferramenta.cpp

        # Classes de Plantas
        src/Cacto.cpp
        src/ErvaDaninha.cpp
        src/Roseira.cpp
        src/Orquidea.cpp

        # Classes de Ferramentas
        src/Adubo.cpp
        src/Regador.cpp
        src/TesouraPoda.cpp
        src/AceleradorCrescimento.cpp

        # Comandos
        src/Comando.cpp
        src/ComandosTodos.cpp
)

target_include_directories(TP PUBLIC ${CMAKE_SOURCE_DIR}/include)