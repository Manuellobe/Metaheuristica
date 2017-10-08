cmake_minimum_required(VERSION 3.8)
project(Metaheuristica)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Metaheuristica.cpp interferencia.cpp interferencia.h transmisor.cpp transmisor.h Metaheuristica.h frecuencia.h)
add_executable(Metaheuristica ${SOURCE_FILES})