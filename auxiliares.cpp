#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}


/************++*********************** Auxiliares tiempoTotal ************++*********************/
tiempo minimoTiempo(viaje v) {      /*  saca el tiempo minimo */
    tiempo mini = obtenerTiempo(v[0]);
    for (int i =0; i <v.size(); i++) {
        if ( mini > obtenerTiempo(v[i])) {
            mini = obtenerTiempo(v[i]);
        }
    }
    return mini;
}

tiempo maximoTiempo(viaje v) {   /*  saca el tiempo maximo */
    tiempo max = obtenerTiempo(v[0]);
    for (int i =0; i <v.size(); i++) {
        if ( max < obtenerTiempo(v[i])) {
            max = obtenerTiempo(v[i]);
        }
    }
    return  max;
}


/************++*********************** auxiliares distanciaTotal ************++*********************/
void swapNuevo ( viaje &v , int i, int j) {
        tuple <tiempo, gps> k= v[i];
        v[i]= v[j];
        v[j]=k;
    }

void seleccionarMinimo ( viaje &v , int i) {
    int posMinimo = i;
    for(int j=i; j< v.size () ; j++) {
        if( obtenerTiempo(v[posMinimo]) > obtenerTiempo(v[j])) {
            posMinimo = j;
        }
    }
    swapNuevo(v ,i, posMinimo ) ;
}



    viaje viajeOrdenadoNuevo (viaje v) {
        for(int i=0; i < v.size() ; i++) {
            seleccionarMinimo (v ,i) ;
        }
        return v;
    }
/***  uso de selection sort dado por la practica ***/



/************++*********************** auxiliares excesodevelocidad ************++*********************/

double  velocidadEntrepuntos(tuple <tiempo, gps> i , tuple <tiempo, gps> j) {
    double v = distEnKM(obtenerPosicion(i),obtenerPosicion(j))/((obtenerTiempo(j) - obtenerTiempo(i))/3600);

    return v;
}

/************++*********************** auxiliares flota ************++*********************/

bool estaEnRango (viaje f, tiempo t0, tiempo tf ){
bool res = false;
    if ( !(((t0 < minimoTiempo(f)) && (tf < minimoTiempo(f)))  || ((t0 > maximoTiempo(f)) && (tf > maximoTiempo(f))))){
    res = true;

}
    return res ;
}

/************++*********************** auxiliares RecorridoNoCubierto ************++*********************/

bool cubierto(viaje v, gps r, distancia u){
   bool res = false;
    for(int i = 0; i<v.size(); i++)
        if ( distEnKM(obtenerPosicion(v[i]), r) < u){
            res = true;
            break;
        }
    return res;

}

/************++*********************** auxiliares counstruirGrilla ************++*********************/

gps esquinaIzquierda (int i , int j,  gps esq1,  gps esq2 , int  n , int  m){           /**** Crea la esquina Superior ***/
    gps esqizq;
    get<0>(esqizq) = obtenerLatitud(esq1) - ((obtenerLatitud(esq1)- obtenerLatitud(esq2))/n) * (i - 1);
    get<1>(esqizq) =  obtenerLongitud(esq1) + (( obtenerLongitud(esq2)- obtenerLongitud(esq1))/m) * (j - 1);
    return esqizq;
}

gps esquinaDerecha (int i , int j,  gps esq1,  gps esq2 , int  n , int  m){       /**** Crea la esquina inferior ***/
    gps esqder;
    get<0>(esqder) = obtenerLatitud(esquinaIzquierda ( i ,  j,   esq1,   esq2 ,   n ,   m)) - ((obtenerLatitud(esq1)- obtenerLatitud(esq2))/n);
    get<1>(esqder) = obtenerLongitud(esquinaIzquierda ( i ,  j,   esq1,   esq2 ,   n ,   m))  +  ((obtenerLongitud(esq2) - obtenerLongitud(esq1))/m);
    return esqder;
}


/************++*********************** auxiliares cantidadDeSaltos ************++*************** ***/

nombre esCelda( gps t , grilla g){
    nombre celda;
        for (int  j = 0; j < g.size(); j++) {
          if  ( ( get<0>(get<0>(g[j]))  < get<0>(t) <= get<0>(get<1>(g[j]))  ) &&
         ( get<1>(get<0>(g[j])) <=  get<1>(t)   < get<1>(get<1>(g[j])))) {

              celda = get<2>(g[j]);
              break;

          }

    }

    return celda;

}


int CantidadSaltos (nombre n, nombre n1 ){
    if ( sqrt(pow(get<0>(n) - get<0>(n1),2)  + pow(get<1>(n) - get<1>(n1),2) ) >= 2) {
        return 1;
    } else {
        return 0;

    }


}
/************++*********************** auxiliares CorregirViaje ************++*************** ***/

void swapNuevoErrores ( vector<tiempo> &e , int i, int j) {
    tiempo k= e[i];
    e[i]= e[j];
    e[j]=k;
}

void seleccionarMinimoErrores ( vector<tiempo> &e , int i) {
    int posMinimo = i;
    for(int j=i; j< e.size () ; j++) {
        if( e[posMinimo] > e[j]) {
            posMinimo = j;
        }
    }
    swapNuevoErrores(e ,i, posMinimo ) ;
}


vector<tiempo> erroresOrdenado (vector<tiempo> e) {
    for(int i=0; i < e.size() ; i++) {
        seleccionarMinimoErrores (e ,i) ;
    }
    return e;
}

double absoluto (double x){
    if (x > 0){
        return x;
    } else {
        return -x;
    }

}


bool PerteneceAErrores(tiempo v , vector<tiempo> errores){
    if(errores.size()==0)
        return false;
    else {
        int i=0;
        bool pertenece = true;
        while( (i < errores.size()) && pertenece){
            pertenece = errores[i] != v;
            i++;
        }
        return !pertenece;
    }
}


double VelocidadLatitud ( tuple<tiempo,gps> x , tuple<tiempo,gps> y){
    double velLat;
    velLat = ((obtenerLatitud(get<1>(y)))-obtenerLatitud(get<1>(x)))/(get<0>(y)-get<0>(x));
    return velLat;

}


double VelocidadLongitud ( tuple<tiempo,gps> x , tuple<tiempo,gps> y){
    double velLong;
    velLong = ((obtenerLongitud(get<1>(y)))-obtenerLongitud(get<1>(x)))/(get<0>(y)-get<0>(x));
    return velLong;

}

void PuntoCorregido ( tuple<tiempo,gps> &errado,  tuple<tiempo,gps> x,  tuple<tiempo,gps> y ){
    get<0>(get<1>(errado)) = obtenerLatitud(get<1>(x)) + VelocidadLatitud(x, y) *(obtenerTiempo(errado) - obtenerTiempo(x));
    get<1>(get<1>(errado)) = obtenerLongitud(get<1>(x)) + VelocidadLongitud(x, y) *(obtenerTiempo(errado) - obtenerTiempo(x));
    return;

}

Cercanos MasCercanos( viaje e , int error , vector<tiempo> errores) {
    int masCerca = 0;
    for(int j=0; j< e.size () ; j++) {
        if( obtenerTiempo(e[j]) != obtenerTiempo(e[error]) && absoluto (obtenerTiempo(e[j]) - obtenerTiempo(e[error])) < absoluto( obtenerTiempo(e[masCerca]) - obtenerTiempo(e[error]))
        && !PerteneceAErrores(obtenerTiempo(e[j]), errores)) {
            masCerca = j;
        }
    }
        int masCerca2 = 0;
    for(int i=0; i< e.size () ; i++) {
        if( obtenerTiempo(e[i]) != obtenerTiempo(e[error]) && absoluto (obtenerTiempo(e[i]) - obtenerTiempo(e[error])) <  absoluto (obtenerTiempo(e[masCerca]) - obtenerTiempo(e[error]))
           && masCerca != i && !PerteneceAErrores(obtenerTiempo(e[i]), errores)) {
            masCerca2 = i;
        }
    }


return make_tuple(e[masCerca],e[masCerca2]);
}

