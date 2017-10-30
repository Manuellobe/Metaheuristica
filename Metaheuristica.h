//
// Created by manue on 05/10/2017.
//

#ifndef METAHEURISTICA_UTILITIES_H
#define METAHEURISTICA_UTILITIES_H

#include <iostream>
#include "transmisor.h"
#include "interferencia.h"
#include "frecuencia.h"
#include "random.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

class Metaheuristica {

private:
    vector<transmisor> vTransmisores;
    vector<int> indiceTrans;
    vector<vector<Frecuencia> > vDominios;
    vector<vector<int>> indiceFrec;
    list<list<interferencia> > lInterferencias;
    unsigned int coste;

    clock_t startTime;
    clock_t timePassed;

public:
    Metaheuristica();
    void cargarDatos(string ruta);
    void greedy();
    void busquedaLocal();
    void grasp();
    pair<vector<transmisor>,bool> generarSVecinos(vector<transmisor> nVTrans, vector<vector<Frecuencia>> nVDom, unsigned int iteraciones);

};

#endif //METAHEURISTICA_UTILITIES_H
