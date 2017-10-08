#include "Metaheuristica.h"//
// Created by Manuel on 28/09/2017.
//

#include "Metaheuristica.h"

using namespace std;


Metaheuristica::Metaheuristica() {

    //Transmisor base
    transmisor trans(0);
    //Inicializamos el vector de transmisores con 1000 posiciones
    vTransmisores = vector<transmisor>(1000, trans);

    //Inicializamos el vector de dominios con 10 posiciones
    vDominios = vector<vector<Frecuencia>>(10);
    indices = vector<vector<Frecuencia *>>(10);

    //Inicializamos la lista de interferencias
    lInterferencias = list<list<interferencia>>();
    lInterferencias.push_back(list<interferencia>());
}


//region Carga de ficheros

/// Cargamos los datos de los ficheros var, dom y ctr pertenecientes a la ruta @ruta en la eedd correspondiente
/// \param vTrans : vector de transmisores
/// \param vDom : vector de dominios
/// \param lInter : lista de interferencias
/// \param ruta : ruta del directorio
void Metaheuristica::cargarDatos(string ruta) {

    string line;
    int pos;

    //region Transmisores

    ifstream fTrans("../datos/" + ruta + "/var.txt");

    if (fTrans.is_open()) {
        transmisor nTrans(0);
        while (getline(fTrans, line)) {
            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss},
                                  istream_iterator<string>{}};
            if (tokens.size() != 0) {
                nTrans = transmisor(atoi(tokens[1].c_str()));
                pos = atoi(tokens[0].c_str());
                vTransmisores.at(pos) = nTrans;
            }
        }
        fTrans.close();
    }

    //endregion

    //region Rangos de frecuencias

    fTrans.open("../datos/" + ruta + "/dom.txt");

    if (fTrans.is_open()) {
        while (getline(fTrans, line)) {
            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss},
                                  istream_iterator<string>{}};
            if (tokens.size() != 0) {
                pos = atoi(tokens[0].c_str());
                for (int i = 1; i < tokens.size(); i++) {
                    Frecuencia nFre(atoi(tokens[i].c_str()));
                    vDominios.at(pos).push_back(nFre);
                    Frecuencia *pFrecuencia = new Frecuencia(nFre);
                    indices.at(pos).push_back(pFrecuencia);
                }
            }
        }
        fTrans.close();
    }

    //endregion

    //region Interferencias

    fTrans.open("../datos/" + ruta + "/ctr.txt");

    if (fTrans.is_open()) {
        list<list<interferencia>>::iterator it = lInterferencias.begin();
        while (getline(fTrans, line)) {
            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss},
                                  istream_iterator<string>{}};
            if (tokens.size() != 0) {
                if (tokens[2] == "C") {
                    interferencia inter = interferencia(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()),
                                                        atoi(tokens[4].c_str()), atoi(tokens[5].c_str()));
                    if (it->empty()) {
                        it->push_back(inter);
                    } else if (it->begin()->getTrans1() == inter.getTrans1()) {
                        it->push_back(inter);
                    } else {
                        lInterferencias.push_back(list<interferencia>());
                        it++;
                        it->push_back(inter);
                    }
                }
            }
        }
        fTrans.close();
    }

    //endregion

}

//endregion

void Metaheuristica::aGreedy(){
    unsigned int rFrecuencia;
    vector<Frecuencia*>::iterator randPos;
    for (auto &vTran : vTransmisores) {
        if(vTran.getFrecuencia() != 0) {
            rFrecuencia = vTran.getRangoF();
            if (!vDominios.at(rFrecuencia).empty()) {
                randPos = indices.at(rFrecuencia).begin() + rand() % indices.at(rFrecuencia).size();
                vTran.setFrecuencia((*randPos)->getFrecuencia());
                (*randPos)->setUso(true);
                indices.at(rFrecuencia).erase(randPos);
            }
        }
    }

    unsigned int coste = 0;

    for(auto &lista : lInterferencias){
        for(auto &inter : lista){
            if(vTransmisores.at(inter.getTrans1()).getFrecuencia() + vTransmisores.at(inter.getTrans2()).getFrecuencia() > inter.getLimite())
                coste+=inter.getCoste();
        }
    }

}

//TODO: Usar busqueda binaria en el algoritmo Busqueda Local!