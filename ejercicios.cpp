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
    vector<gps> resp;
    // codigo

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); i++)
       if ( !(((t0 < minimoTiempo(f[i])) && (tf < minimoTiempo(f[i])))  || ((t0 > maximoTiempo(f[i])) && (tf > maximoTiempo(f[i]))))){
           resp = resp + 1;

        }

    return resp;
}


/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    // codigo

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp;
    // codigo

    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    return;
}
