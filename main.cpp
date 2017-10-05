#include <iostream>
#include <vector>
#include <list>

#include "utilities.h"

using namespace std;

int main() {

    //Transmisor base
    transmisor trans = transmisor(0);
    //Inicializamos el vector de transmisores con 1000 posiciones
    vector<transmisor> vTransmisores(1000, trans);


    //Inicializamos el vector de dominios con 10 posiciones
    vector<vector<int> > vDominios(10);


    //Inicializamos la lista de interferencias
    list<list<interferencia>> lInterferencias = list<list<interferencia>>();
    lInterferencias.push_back(list<interferencia>());


    //Cargamos los ficheros de cada prueba
    cargarDatos(&vTransmisores, &vDominios, &lInterferencias, "ejemplo");

    return 0;
}