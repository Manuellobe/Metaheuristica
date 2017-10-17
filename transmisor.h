//
// Created by manue on 28/09/2017.
//

#ifndef METAHEURISTICA_TRANSISTOR_H
#define METAHEURISTICA_TRANSISTOR_H


#include "interferencia.h"
#include "frecuencia.h"
#include <list>

using namespace std;

class transmisor {

private:
    unsigned int rangoF;
    Frecuencia frecuencia;


public:
    explicit transmisor(unsigned int Rango);

    explicit transmisor(unsigned int Rango, unsigned int frecuencia);

    int getRangoF() const;

    void setRangoF(unsigned int rangoF);

    Frecuencia getFrecuencia() const;

    void setFrecuencia(Frecuencia frecuencia);
};


#endif //METAHEURISTICA_TRANSISTOR_H
