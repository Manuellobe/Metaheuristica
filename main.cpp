#include <iostream>
#include <vector>
#include <list>

#include "transmisor.h"
#include <fstream>


using namespace std;

int main() {

    //Vector de transmisores
    vector<transmisor> Vtransmisores = vector<transmisor>();

    //Vector de arrays de enteros d dominio de las frecuencias
    vector<vector<int> > Vdominios = vector<vector<int> >();

    list<list<interferencia>> Linterferencias = list<list<interferencia>>();

    string line;
    ifstream  Fdominios("datos/ejemplo/dom.txt");
    if(Fdominios.is_open()){
        while (getline(Fdominios,line)){
            cout<<"Holi Danija, en tu pc funsiona y en el mio no :D"<<endl;
        }
        Fdominios.close();
    }




    return 0;
}