cmake_minimum_required(VERSION 3.30)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP main.cpp Adubo.cpp BocadoSolo.cpp Cacto.cpp ErvaDaninha.cpp EstaSolo.cpp Ferramenta.cpp Jardim.cpp Planta.cpp Regador.cpp Roseira.cpp TesouraPoda.cpp
        Interface.cpp Simulador.cpp Comando.cpp ComandosTodos.cpp Jardineiro.cpp
        Orquidea.h
        Orquidea.cpp)