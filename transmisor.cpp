//
// Created by manue on 28/09/2017.
//

#include "transmisor.h"

transmisor::transmisor(int Rango) {
    this->rangoF = Rango;
    this->frecuencia = -1;
}

int transmisor::getRangoF() const {
    return rangoF;
}

void transmisor::setRangoF(int rangoF) {
    transmisor::rangoF = rangoF;
}

int transmisor::getFrecuencia() const {
    return frecuencia;
}

void transmisor::setFrecuencia(int frecuencia) {
    transmisor::frecuencia = frecuencia;
}
