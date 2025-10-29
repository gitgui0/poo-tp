cmake_minimum_required(VERSION 3.30)
project(TP)

set(CMAKE_CXX_STANDARD 20)

# Include de todas as pastas header
include_directories(
        include
        include/plantas
        include/ferramentas
        include/jardim
)

# encontra todos os .cpp ---
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
