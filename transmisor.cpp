//
// Created by manue on 28/09/2017.
//

#include "transmisor.h"

transmisor::transmisor(unsigned int Rango):frecuencia(pair<int, int>(-1,0)) {
    this->rangoF = Rango;
}

transmisor::transmisor(unsigned int Rango, unsigned int frecuencia):frecuencia(pair<int, int>(frecuencia,0)) {
    this->rangoF = Rango;
}

int transmisor::getRangoF() const {
    return rangoF;
}

void transmisor::setRangoF(unsigned int rangoF) {
    this->rangoF = rangoF;
}

Frecuencia transmisor::getFrecuencia() const {
    return frecuencia;
}

void transmisor::setFrecuencia(Frecuencia frecuencia) {
    this->frecuencia = frecuencia;
}
