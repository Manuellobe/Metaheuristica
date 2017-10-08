//
// Created by manue on 08/10/2017.
//

#ifndef METAHEURISTICA_FRECUENCIA_H
#define METAHEURISTICA_FRECUENCIA_H


class Frecuencia {
private:
    int frecuencia;
    bool enUso;
public:
    explicit Frecuencia(int nFrec) { this->frecuencia = nFrec; this->enUso = false; }
    explicit Frecuencia(const Frecuencia &nFrec) { this->frecuencia = nFrec.frecuencia; this->enUso = nFrec.enUso; }
    bool isUsed() { return this->enUso; }
    void setUso(bool usada) { this->enUso = usada; }
    int getFrecuencia() { return this->frecuencia; }
};


#endif //METAHEURISTICA_FRECUENCIA_H
