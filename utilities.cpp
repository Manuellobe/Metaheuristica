//
// Created by Manuel on 28/09/2017.
//

#include "utilities.h"

using namespace std;

//region Carga de ficheros

/// Cargamos los datos de los ficheros var, dom y ctr pertenecientes a la ruta @ruta en la eedd correspondiente
/// \param vTrans : vector de transmisores
/// \param vDom : vector de dominios
/// \param lInter : lista de interferencias
/// \param ruta : ruta del directorio
void cargarDatos(vector<transmisor> *vTrans, vector<vector<int>> *vDom, list<list<interferencia>> *lInter, string ruta) {

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
                vTrans->at(pos) = nTrans;
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
                    vDom->at(pos).push_back(atoi(tokens[i].c_str()));
                }
            }
        }
        fTrans.close();
    }

    //endregion

    //region Interferencias

    fTrans.open("../datos/" + ruta + "/ctr.txt");

    if (fTrans.is_open()) {
        list<list<interferencia>>::iterator it = lInter->begin();
        while (getline(fTrans, line)) {
            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss},
                                  istream_iterator<string>{}};
            if (tokens.size() != 0) {
                if (tokens[2] == "C") {
                    interferencia inter = interferencia(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()),
                                                        atoi(tokens[4].c_str()), atoi(tokens[5].c_str()));
                    if (it->empty()) {
                        //lInter->push_back(list<interferencia>());
                        it->push_back(inter);
                    } else if (it->begin()->getTrans1() == inter.getTrans1()) {
                        it->push_back(inter);
                    } else {
                        lInter->push_back(list<interferencia>());
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
