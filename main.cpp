#include <iostream>
#include <vector>
#include <list>

#include "Metaheuristica.h"

using namespace std;

int main() {

    Metaheuristica algoritmos = Metaheuristica();

    string semilla;

    ifstream fSemilla("../semilla.txt");

    if (fSemilla.is_open()) {
        getline(fSemilla, semilla);
        istringstream iss(semilla);
        vector<string> tokens{istream_iterator<string>{iss},
                              istream_iterator<string>{}};
        if (tokens.size() != 0) {
            Seed = atoi(tokens[0].c_str());
            cout<<"Semilla: "<<Seed<<endl;
        }
        else
            cout<<"Numero de parametros incorrecto"<<endl;

        fSemilla.close();

        string line;

        ifstream fRuta("../ruta.txt");

        if (fRuta.is_open()) {
            getline(fRuta, line);
            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss},
                                  istream_iterator<string>{}};
            if (tokens.size() != 0) {
                line = tokens[0].c_str();
            }
            else
                cout<<"Numero de parametros incorrecto"<<endl;

            fRuta.close();

            //Cargamos los ficheros
            algoritmos.cargarDatos(line);

            algoritmos.greedy();
            algoritmos.grasp();
            algoritmos.busquedaLocal();
        }
        else
            cout<<"No se ha podido abrir el fichero ruta.txt"<<endl;

    }
    else
        cout<<"No se ha podido abrir el fichero semilla.txt"<<endl;


    return 0;
}