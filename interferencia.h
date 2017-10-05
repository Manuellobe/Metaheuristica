//
// Created by manue on 28/09/2017.
//

#ifndef METAHEURISTICA_INTERFERENCIA_H
#define METAHEURISTICA_INTERFERENCIA_H


class interferencia {

private :
    int trans1, trans2, limite, coste;

public:
    interferencia(int Trans1, int Trans2, int Limite, int Coste);
    int getTrans1() { return trans1; }
    int getTrans2(){ return trans2; }
    int getLimite(){ return limite; }
    int getCoste(){ return coste; }
};


#endif //METAHEURISTICA_INTERFERENCIA_H
