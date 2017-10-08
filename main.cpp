#include <iostream>
#include <vector>
#include <list>

#include "Metaheuristica.h"

using namespace std;

int main() {

    Metaheuristica algoritmos = Metaheuristica();

    //Cargamos los ficheros de cada prueba
    algoritmos.cargarDatos("graph05");


    algoritmos.aGreedy();

    return 0;
}