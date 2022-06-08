#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t = 0;   /****** 1 *****/
    tiempo min = minimoTiempo(v);   /***** en el peor caso se ejecuta n veces  *****/
    tiempo  max = maximoTiempo(v); /***** en el peor caso se ejecuta n veces  *****/
    return t = max - min;   /**** 2 ***/
 }

 /*****  2n + 3 = O(n)  ******/

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d = 0; /****  1  ***/
   viaje t = viajeOrdenadoNuevo(v);       /*** se ejecuta n^2 veces ya que usa algoritmo de selection sortt ***/
    for(int i=0; i<v.size()-1;i++){            /*****  se ejecuta en el peor caso n veces ***/
        d= distEnKM(obtenerPosicion(t[i]),obtenerPosicion(t[i+1])) + d;

    }

    return d;  /*** 1  ***/
}

/******   n^2 + n + 2  = O(n^2) **** /


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
    vector<gps> resp = {};   /***** 1 vez  ****/
    for(int i = 0; i<r.size();i++){    /******* En el peor caso se ejecuta la  m veces que es el tamaño de r  ***/
    if(!cubierto(v, r[i], u)){              /******* En el peor caso se ejecuta la  n veces que es el tamaño de v  ***/
        resp.push_back(r[i]);           /***** 1     *****/
        }
        }
    return resp;     /*****  1 vez  ******/
}

/***** se ejecuta m x n + 3 veces en el peor de casos, es decir O( n x m)     ****/


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
    for(int k =0; k < t.size();k++ ) {
               n.push_back( esCelda(obtenerPosicion(t[k]), g ));
            }


    int resp = 0;
    for (int j = 0; j < n.size()-1;j++){
      resp = CantidadSaltos(n[j], n[j+1]) + resp;
    }
    return resp;
}
/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){

    for(int i = 0; i < v.size(); i++){
            if  (PerteneceAErrores(obtenerTiempo(v[i]), errores) ){
              PuntoCorregido(v[i], get<0>(MasCercanos(v, i , errores)), get<1>(MasCercanos(v,i,errores)));

                }
        }


    return;
}
