cmake_minimum_required(VERSION 3.30)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP
        # Núcleo e Interface
        main.cpp
        src/simulacao/Simulador.cpp
        src/simulacao/Interface.cpp

        # Domínio (Jardim, Solo e Jardineiro)
        src/jardim/Jardim.cpp
        src/jardim/BocadoSolo.cpp
        src/jardim/Jardineiro.cpp

        # Classes Base
        src/jardim/EstaSolo.cpp
        src/plantas/Planta.cpp
        src/ferramentas/Ferramenta.cpp

        # Classes de Plantas
        src/plantas/Cacto.cpp
        src/plantas/ErvaDaninha.cpp
        src/plantas/Roseira.cpp
        src/plantas/Orquidea.cpp

        # Classes de Ferramentas
        src/ferramentas/Adubo.cpp
        src/ferramentas/Regador.cpp
        src/ferramentas/TesouraPoda.cpp
        src/ferramentas/AceleradorCrescimento.cpp

        # Comandos
        src/simulacao/Comando.cpp
        src/simulacao/ComandosTodos.cpp
        include/simulacao/SettingsExtra.h
)

# Atualizado para incluir as subpastas da pasta 'include'
target_include_directories(TP PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/jardim
        ${CMAKE_SOURCE_DIR}/include/plantas
        ${CMAKE_SOURCE_DIR}/include/ferramentas
        ${CMAKE_SOURCE_DIR}/include/simulacao
)