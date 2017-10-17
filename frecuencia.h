//
// Created by manue on 08/10/2017.
//

#ifndef METAHEURISTICA_FRECUENCIA_H
#define METAHEURISTICA_FRECUENCIA_H

#include <utility>


class Frecuencia {
private:
    std::pair<int, int> frecuencia;//first: frecuencia / second: indice
    bool enUso;
public:
    Frecuencia() {}
    Frecuencia(std::pair<int, int> nFrec) { this->frecuencia.first = nFrec.first;
        this->frecuencia.second = nFrec.second;this->enUso = false; }
    Frecuencia(const Frecuencia &nFrec): frecuencia(nFrec.frecuencia) { this->enUso = nFrec.enUso; }
    bool isUsed() { return this->enUso; }
    void setUso(bool usada) { this->enUso = usada; }
    std::pair<int, int> getFrecuencia() { return this->frecuencia; }
};


#endif //METAHEURISTICA_FRECUENCIA_H
