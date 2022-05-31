#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t;
    tiempo min = minimoTiempo(v);
    tiempo  max = maximoTiempo(v);
    return t = max - min;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d = 0;
   viaje t = viajeOrdenadoNuevo(v);
    for(int i=0; i<v.size()-1;i++){
        d= distEnKM(obtenerPosicion(t[i]),obtenerPosicion(t[i+1])) + d;

    }

    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    viaje t = viajeOrdenadoNuevo(v);
    for( int i=0; i<v.size()-1; i++) {
        if (velocidadEntrepuntos( t[i], t[i+1]) > 80){
            resp = true;
            break;
        }
    }
    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp = {};
    for(int i = 0; i<r.size();i++){
    if(!cubierto(v, r[i], u)){
        resp.push_back(r[i]);
        }
        }
    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); i++)
       if ( estaEnRango ( f[i],  t0, tf )){
           resp = resp + 1;

        }

    return resp;
}


/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1; j <= m; j++) {
            resp.push_back( make_tuple(esquinaIzquierda(i, j, esq1, esq2, n, m), esquinaDerecha(i, j, esq1, esq2, n, m), make_tuple(i,j)));
        }
    }
    return resp;
}


/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    viaje t = viajeOrdenadoNuevo(v);
    vector<nombre> n;
    for(int k = 0; k<g.size(); k++) {
        for (int i = 0; i < t.size(); i++) {
            if (esCelda(obtenerPosicion(t[i]), g[k])) {
                n.push_back(get<2>(g[k]));
            }
        }
    }

    int resp = 0;
    for (int j = 0; j< n.size()-1;j++){
        resp = CantidadSaltos(n[j], n[j+1]) + resp;
    }
    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    return;
}
