//
// Created by manue on 28/09/2017.
//

#ifndef METAHEURISTICA_TRANSISTOR_H
#define METAHEURISTICA_TRANSISTOR_H


#include "interferencia.h"
#include <list>

using namespace std;

class transmisor {

private:
    unsigned int rangoF, frecuencia;


public:
    explicit transmisor(unsigned int Rango);

    int getRangoF() const;

    void setRangoF(unsigned int rangoF);

    int getFrecuencia() const;

    void setFrecuencia(unsigned int frecuencia);
};


#endif //METAHEURISTICA_TRANSISTOR_H
