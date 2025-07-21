cmake_minimum_required(VERSION 3.10)
project(HelloWordSFML)

set(CMAKE_CXX_STANDARD 17)

# Trova SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Aggiungi il file sorgente
add_executable(HelloWordSFML src/main.cpp)

# Collega le librerie SFML
target_link_libraries(HelloWordSFML sfml-graphics sfml-window sfml-system)
