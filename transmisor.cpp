//
// Created by manue on 28/09/2017.
//

#include "transmisor.h"

transmisor::transmisor(unsigned int Rango) {
    this->rangoF = Rango;
    this->frecuencia = 0;
}

int transmisor::getRangoF() const {
    return rangoF;
}

void transmisor::setRangoF(unsigned int rangoF) {
    transmisor::rangoF = rangoF;
}

int transmisor::getFrecuencia() const {
    return frecuencia;
}

void transmisor::setFrecuencia(unsigned int frecuencia) {
    transmisor::frecuencia = frecuencia;
}
