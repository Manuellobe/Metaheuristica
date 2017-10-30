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

void Metaheuristica::greedy(){

    unsigned int rFrecuencia;

    vector<vector<Frecuencia>> nFrec = vDominios;
    vector<transmisor> nTrans = vTransmisores;
    vector<vector<int>> copiaIndiceFrec = indiceFrec;

    coste = 0;
    vector<int>::iterator randPos;

    startTime = clock();

    for (auto &vTran : nTrans) {
        if (vTran.getFrecuencia().getFrecuencia().first == 0) {
            rFrecuencia = vTran.getRangoF();
            if (!copiaIndiceFrec.at(rFrecuencia).empty()) {

                randPos = copiaIndiceFrec.at(rFrecuencia).begin() + Randint(0, copiaIndiceFrec.at(rFrecuencia).size() - 1);

                vTran.setFrecuencia(nFrec.at(rFrecuencia).at((*randPos)).getFrecuencia());
                nFrec.at(rFrecuencia).at((*randPos)).setUso(true);
                copiaIndiceFrec.at(rFrecuencia).erase(randPos);
            }
        }
    }


    for (auto &lista : lInterferencias) {
        for (auto &inter : lista) {
            if (nTrans.at(inter.getTrans1()).getFrecuencia().getFrecuencia().first +
                nTrans.at(inter.getTrans2()).getFrecuencia().getFrecuencia().first > inter.getLimite())
                coste += inter.getCoste();
        }
    }

    timePassed = clock();

    cout<<(timePassed - startTime)/ (double) CLOCKS_PER_SEC<<endl;

    cout << "Solucion final Greedy:" << endl;
    cout << coste << endl;
}


void Metaheuristica::busquedaLocal() {
    unsigned int rFrecuencia;
    vector<vector<Frecuencia>> nFrec = vDominios;
    vector<transmisor> nTrans = vTransmisores;
    vector<vector<int>> copiaIndiceFrec = indiceFrec;
    coste = 0;
    vector<int>::iterator randPos;
    for (auto &vTran : nTrans) {
        if (vTran.getFrecuencia().getFrecuencia().first == 0) {
            rFrecuencia = vTran.getRangoF();
            if (!copiaIndiceFrec.at(rFrecuencia).empty()) {

                randPos = copiaIndiceFrec.at(rFrecuencia).begin() + Randint(0, copiaIndiceFrec.at(rFrecuencia).size() - 1);

                vTran.setFrecuencia(nFrec.at(rFrecuencia).at((*randPos)).getFrecuencia());
                nFrec.at(rFrecuencia).at((*randPos)).setUso(true);
                copiaIndiceFrec.at(rFrecuencia).erase(randPos);
            }
        }
    }


    for (auto &lista : lInterferencias) {
        for (auto &inter : lista) {
            if (nTrans.at(inter.getTrans1()).getFrecuencia().getFrecuencia().first +
                        nTrans.at(inter.getTrans2()).getFrecuencia().getFrecuencia().first > inter.getLimite())
                coste += inter.getCoste();
        }
    }

    pair<vector<transmisor>, bool> sVecina = generarSVecinos(nTrans, nFrec, 1000);
    while (sVecina.second) {
        sVecina = generarSVecinos(sVecina.first, nFrec, 1000);
    }

    cout << "Solucion final BL:" << endl;
    cout << coste << endl;


}


void Metaheuristica::grasp() {

    vector<transmisor> mejorSolucion;
    int mejorCoste = 9999;

    for(int i = 0; i < 25; i++) {

        // Coste por defecto
        coste = 9999;

        vector<transmisor> vTrans = vTransmisores;
        vector<int> copiaIndTrans = indiceTrans;
        vector<vector<Frecuencia>> vFrec = vDominios;
        vector<vector<int>> copiaIndFrec = indiceFrec;

        vector<transmisor> solucionActual = vTrans;

        int k = 10;
        int j = 0;
        int posFrec, rFrecuencia;
        vector<int>::iterator posTrans;

        // Crear LRC

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

        // Restablecemos k para futuros calculos
        k = 10;

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

        //Ordenar vectorCostes

        sort(vectorCostes.begin(), vectorCostes.end());

        vector<float> calculoPorPosicion;

        float sucesionArmonica = 0.0f;

        for (int i = 0; i <= vectorCostes.size(); i++) {
            sucesionArmonica += 1.0f / (i + 1);
            calculoPorPosicion.push_back(sucesionArmonica);
        }

        // Obtener solucion    pos/(total-1)

        double valorAleatorio;
        int posValorExtraido;
        int min, max;
        vector<pair<int, int>>::iterator vectorCostesIt;

        while (vectorCostes.size() != k) {
            valorAleatorio = Rand();
            posValorExtraido = -1;
            min = 0;
            max = vectorCostes.size() - 1;
            while (posValorExtraido == -1) {

                //Calculo posicion intermedia
                int posIntermedia = round((max - min) / 2.0) + min;
                float valorArmonico = calculoPorPosicion[vectorCostes.size() - 1];


                //Comprobacion del valor de las posiciones con el valor deseado
                if ((1 / (float) posIntermedia) / valorArmonico > valorAleatorio) {

                    if ((1 / (float) posIntermedia + 1) / valorArmonico < valorAleatorio) {
                        //Comprobar entre el valor actual y el anterior cual es el mas cercano a valorAleatorio
                        float valorPosActual, valorPosPrevia;
                        valorPosActual = (1 / (float) posIntermedia + 1) / valorArmonico;
                        valorPosPrevia = (1 / (float) posIntermedia) / valorArmonico;
                        if (valorAleatorio - valorPosPrevia >= valorPosActual - valorAleatorio)
                            posValorExtraido = posIntermedia - 1;
                        else
                            posValorExtraido = posIntermedia;
                    } else {
                        if (max - min <= 1)
                            posValorExtraido = max;
                        else
                            //Volver a empezar con un nuevo min y max
                            min = posIntermedia;
                    }
                } else {
                    if (max - min <= 1)
                        posValorExtraido = min;
                    else {
                        //Volver a empezar con un nuevo min y max
                        if (vectorCostes.size() % 2 == 0)
                            max = posIntermedia - 1;
                        else
                            max = posIntermedia;
                    }
                }
            }

            solucionActual.at(vectorCostes.at(posValorExtraido).second) = vTrans.at(
                    vectorCostes.at(posValorExtraido).second);
            vectorCostesIt = vectorCostes.begin() + posValorExtraido;
            vectorCostes.erase(vectorCostesIt);
        }

        // Asignamos los k transmisores restantes segun el algoritmo greedy

        while (vectorCostes.size() != 0) {

            // Obtengo la mejor frecuencia disponible que coincide con la primera posicion del indice
            unsigned int rangoF = vTrans.at(vectorCostes[0].second).getRangoF();

            auto itInicio = copiaIndFrec.at(vTrans.at(vectorCostes[0].second).getRangoF()).begin();
            while (!copiaIndFrec.at(rangoF).empty() && vFrec.at(rangoF).at((*itInicio)).isUsed()) {
                copiaIndFrec.at(rangoF).erase(itInicio);
                if (!copiaIndFrec.at(rangoF).empty())
                    itInicio = copiaIndFrec.at(vTrans.at(vectorCostes[0].second).getRangoF()).begin();
            }

            if (!copiaIndFrec.at(rangoF).empty()) {
                unsigned int posFrec = (*itInicio);

                // Asigno la frecuencia al primer transmisor del vector de costes
                solucionActual.at(vectorCostes[0].second).setFrecuencia(vFrec.at(rangoF).at(posFrec));

                // Quito lo frecuencia asignada del indice
                copiaIndFrec.at(rangoF).erase(copiaIndFrec.at(rangoF).begin());
            }

            // Quito el transmisor del vector de costes
            vectorCostes.erase(vectorCostes.begin());
        }


        pair<vector<transmisor>, bool> sVecina = generarSVecinos(solucionActual, vFrec, 400);
        while (sVecina.second) {
            sVecina = generarSVecinos(sVecina.first, vFrec, 400);
        }

        if(coste < mejorCoste){
            mejorCoste = coste;
            mejorSolucion = sVecina.first;
        }

    }

    cout << "Solucion final GRASP:" << endl;
    cout << mejorCoste << endl;

}

pair<vector<transmisor>, bool>
Metaheuristica::generarSVecinos(vector<transmisor> nVTrans, vector<vector<Frecuencia>> nVDom,
                                unsigned int iteraciones) {

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
                currentPos = nVDom.at(rFrecuencia).begin() + pos;

                while ((currentPos != nVDom.at(rFrecuencia).begin() - 1 &&
                        currentPos != nVDom.at(rFrecuencia).end())
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

    } while (nCoste >= iteraciones && iteracion <= iteraciones);
    if (nCoste < coste) {
        coste = nCoste;
        return pair<vector<transmisor>, bool>(nVTrans, true);
    } else {
        return pair<vector<transmisor>, bool>(nVTrans, false);
    }


}