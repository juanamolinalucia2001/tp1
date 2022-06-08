#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);
tiempo maximoTiempo(viaje v);
tiempo minimoTiempo(viaje v);
void swap(tuple<tiempo, gps>  a, tuple<tiempo, gps>  b);
void ordenarViaje (viaje &v);
viaje viajeOrdenadoNuevo (viaje v);
double  velocidadEntrepuntos(tuple <tiempo, gps> i , tuple <tiempo, gps> j);
bool cubierto(viaje v, gps r, distancia u);
bool estaEnRango (viaje f, tiempo t0, tiempo tf );
gps esquinaIzquierda (int i , int j,  gps esq1,  gps esq2 , int  n , int  m);
gps esquinaDerecha (int i , int j,  gps esq1,  gps esq2 , int  n , int  m);
nombre esCelda(gps t , grilla g);
int CantidadSaltos (nombre n, nombre n1 );
vector<tiempo> erroresOrdenado (vector<tiempo> e);
bool PerteneceAErrores(tiempo v , vector<tiempo> errores);
Cercanos MasCercanos( viaje e , int error , vector<tiempo> errores);
void PuntoCorregido ( tuple<tiempo,gps> &errado,  tuple<tiempo,gps> x,  tuple<tiempo,gps> y );
void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);

#endif //TRANSPORTEURBANO_AUXILIARES_H
