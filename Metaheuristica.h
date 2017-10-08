//
// Created by manue on 05/10/2017.
//

#ifndef METAHEURISTICA_UTILITIES_H
#define METAHEURISTICA_UTILITIES_H

#include <iostream>
#include "transmisor.h"
#include "interferencia.h"
#include "frecuencia.h"
//#include "random.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdlib.h>

class Metaheuristica {

private:
    vector<transmisor> vTransmisores;
    vector<vector<Frecuencia> > vDominios;
    vector<vector<Frecuencia*>> indices;
    list<list<interferencia> > lInterferencias;
public:
    Metaheuristica();
    void cargarDatos(string ruta);
    void aGreedy();

};

#endif //METAHEURISTICA_UTILITIES_H
