#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosTEST, todosSaltosOrdenados){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), 3000, 3000), 6, 6);

    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, 2000, 2000);
    gps p3 = desviarPunto(p1, 100, 100);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

/*** Test de grupo ***/

TEST(cantidadDeSaltosTEST, todosSaltosDesordenados){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), 3000, 3000), 6, 6);

    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, 2000, 2000);
    gps p3 = desviarPunto(p1, 100, 100);
    gps p4 = desviarPunto(p1, 101, 101);

    viaje v = {medicion(1.9, p1),
               medicion(2.1, p2),
               medicion(2.0, p3),
               medicion(1.7, p4)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}
