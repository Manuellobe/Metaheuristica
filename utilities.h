//
// Created by manue on 05/10/2017.
//

#ifndef METAHEURISTICA_UTILITIES_H
#define METAHEURISTICA_UTILITIES_H

#include <iostream>
#include "transmisor.h"
#include "interferencia.h"
#include <vector>

#include <fstream>
#include <sstream>
#include <iterator>

void cargarDatos(vector<transmisor> * vTrans, vector<vector<int>> * vDom, list<list<interferencia>> * lInter, string ruta);


#endif //METAHEURISTICA_UTILITIES_H
