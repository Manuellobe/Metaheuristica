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
    indiceTrans = vector<int>();
    coste = 0;

    //Inicializamos el vector de dominios con 10 posiciones
    vDominios = vector<vector<Frecuencia>>(10);
    indiceFrec = vector<vector<int>>(10);

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
                nTrans = transmisor(atoi(tokens[1].c_str()), 0);
                pos = atoi(tokens[0].c_str());
                vTransmisores.at(pos) = nTrans;
                indiceTrans.push_back(pos);
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
                    Frecuencia nFre(pair<int, int>(atoi(tokens[i].c_str()), vDominios.at(pos).size()));
                    vDominios.at(pos).push_back(nFre);
                    indiceFrec.at(pos).push_back(vDominios.at(pos).size() - 1);
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
            if (tokens.size() > 1) {
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

void Metaheuristica::busquedaLocal() {
    unsigned int rFrecuencia;
    coste = 0;
    vector<int>::iterator randPos;
    for (auto &vTran : vTransmisores) {
        if (vTran.getFrecuencia().getFrecuencia().first == 0) {
            rFrecuencia = vTran.getRangoF();
            if (!indiceFrec.at(rFrecuencia).empty()) {

                randPos = indiceFrec.at(rFrecuencia).begin() + Randint(0, indiceFrec.at(rFrecuencia).size() - 1);

                vTran.setFrecuencia(vDominios.at(rFrecuencia).at((*randPos)).getFrecuencia());
                vDominios.at(rFrecuencia).at((*randPos)).setUso(true);
                indiceFrec.at(rFrecuencia).erase(randPos);
            }
        }
    }


    for (auto &lista : lInterferencias) {
        for (auto &inter : lista) {
            if (vTransmisores.at(inter.getTrans1()).getFrecuencia().getFrecuencia().first +
                vTransmisores.at(inter.getTrans2()).getFrecuencia().getFrecuencia().first > inter.getLimite())
                coste += inter.getCoste();
        }
    }

    pair<vector<transmisor>, bool> sVecina = generarSVecinos(vTransmisores);
    while (sVecina.second) {
        sVecina = generarSVecinos(sVecina.first);
    }

    cout << "Solucion final:" << endl;
    cout << coste << endl;


}


void Metaheuristica::grasp() {

    // Crear LRC

    vector<transmisor> vTrans = vTransmisores;
    vector<int> copiaIndTrans = indiceTrans;
    vector<vector<Frecuencia>> vFrec = vDominios;
    vector<vector<int>> copiaIndFrec = indiceFrec;

    int k = 50;
    int j = 0;
    int posFrec, rFrecuencia;
    vector<int>::iterator posTrans;
    while (k > 0) {

        posTrans = copiaIndTrans.begin() + Randint(0, copiaIndTrans.size() - 1);
        rFrecuencia = vTrans.at((*posTrans)).getRangoF();
        do {
            posFrec = (Randint(0, vFrec.at(rFrecuencia).size() + j)) % vFrec.at(rFrecuencia).size();
            j++;
        } while (vFrec.at(rFrecuencia).at(posFrec).isUsed());

        vFrec.at(rFrecuencia).at(posFrec).setUso(true);

        vTrans.at((*posTrans)).setFrecuencia(vFrec.at(rFrecuencia).at(posFrec));

        copiaIndTrans.erase(posTrans);

        k--;
    }

    // Creamos un vector de iteradores para tener un acceso directo a la primera frecuencia disponible de cada rango
    vector<int> vIteradores;
    for (int i = 0; i < 8; i++) {
        vIteradores.push_back(0);
    }

    for (auto &trans : vTrans) {
        if (trans.getFrecuencia().getFrecuencia().first == 0) {
            int rangoF = trans.getRangoF();
            int pos = vIteradores.at(rangoF);
            while (pos < vFrec.at(rangoF).size() && vFrec.at(rangoF).at(pos).isUsed()) {
                vIteradores.at(rangoF)++;
                pos = vIteradores.at(rangoF);
            }
            if (pos < vFrec.at(rangoF).size()) {
                vFrec.at(rangoF).at(pos).setUso(true);
                trans.setFrecuencia(vFrec.at(rangoF).at(pos));
                vIteradores.at(rangoF)++;
            }

        }
    }

    // Generar tablas costes

    vector<pair<int, int>> vectorCostes;

    for (auto &lista : lInterferencias) {
        int costeIndividual;
        int nTrans;
        for (auto &inter : lista) {
            costeIndividual = 0;
            if (vTrans.at(inter.getTrans1()).getFrecuencia().getFrecuencia().first +
                vTrans.at(inter.getTrans2()).getFrecuencia().getFrecuencia().first > inter.getLimite()) {
                costeIndividual += inter.getCoste();
                nTrans = inter.getTrans1();
            }
        }
        pair<int, int> costeActual(costeIndividual, nTrans);
        vectorCostes.push_back(costeActual);
    }

    // Obtener solucion

    // Repetir :D



}

pair<vector<transmisor>, bool> Metaheuristica::generarSVecinos(vector<transmisor> nVTrans) {

    unsigned int nCoste;
    int direccion;
    int iteracion = 0;
    bool deboContinuar;
    unsigned int rFrecuencia;

    do {
        for (auto &vTran : nVTrans) {
            if (vTran.getFrecuencia().getFrecuencia().first != -1) {
                rFrecuencia = vTran.getRangoF();
                vector<Frecuencia>::iterator currentPos;
                Randint(0, 1) == 1 ? direccion = 1 : direccion = -1;
                deboContinuar = true;
                int pos = vTran.getFrecuencia().getFrecuencia().second +
                          direccion;
                currentPos = vDominios.at(rFrecuencia).begin() + pos;

                while ((currentPos != vDominios.at(rFrecuencia).begin() - 1 &&
                        currentPos != vDominios.at(rFrecuencia).end())
                       && deboContinuar) {

                    if (!currentPos->isUsed()) {
                        currentPos->setUso(true);
                        vTran.setFrecuencia(*currentPos);
                        currentPos -= direccion;
                        currentPos->setUso(false);
                        deboContinuar = false;
                    } else
                        currentPos += direccion;
                }
            }
        }

        nCoste = 0;

        for (auto &lista : lInterferencias) {
            for (auto &inter : lista) {
                if (nVTrans.at(inter.getTrans1()).getFrecuencia().getFrecuencia().first +
                    nVTrans.at(inter.getTrans2()).getFrecuencia().getFrecuencia().first > inter.getLimite())
                    nCoste += inter.getCoste();
            }
        }
        iteracion++;

    } while (nCoste >= coste && iteracion <= 10000);
    if (nCoste < coste) {
        coste = nCoste;
        return pair<vector<transmisor>, bool>(nVTrans, true);
    } else {
        return pair<vector<transmisor>, bool>(nVTrans, false);
    }


}