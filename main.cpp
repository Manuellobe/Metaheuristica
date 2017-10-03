#include <iostream>
#include <vector>
#include <list>

#include "transmisor.h"
#include <iostream>
#include <fstream>


using namespace std;

int main() {

    //Vector de transmisores
    vector<transmisor> Vtransmisores = vector<transmisor>();
    //Vector de arrays de enteros d dominio de las frecuencias
    vector<vector<int> > Vdominios = vector<vector<int> >();

    list<list<interferencia>> Linterferencias = list<list<interferencia>>();


    //TODO: Carga de transmisores

    //TODO: Carga de dominios
    string line;
    ifstream  Fdominios("datos/ejemplo/dom.txt");
    if(Fdominios.is_open()){
        while (Fdominios.good()){
            getline(Fdominios,line);

        }
        Fdominios.close();
    }




    return 0;
}