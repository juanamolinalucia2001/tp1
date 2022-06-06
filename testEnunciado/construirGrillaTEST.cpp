#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(construirGrillaTEST, nombresCorrectosDistanciaParNParMImparArg){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                  make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                  make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                  make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                  make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                  make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
                  };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
}

/*****  El test suite dado  cubre las lineas ****/

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}


TEST (sonGrillasIguales, soniguales){
    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres2 = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                   make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                   make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                   make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                   make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                   make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
    };

    grilla g2 = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g2.size());
    ASSERT_ELEMENTS( gres2,  g2);
}