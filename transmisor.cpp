//
// Created by manue on 28/09/2017.
//

#include "transmisor.h"

transmisor::transmisor(int Rango) {
    this->rango = Rango;
    this->frecuencia = -1;
    this->interferencias = list<interferencia>();
}