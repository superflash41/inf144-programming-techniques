// Proyecto: LongitudYAreaBajoUnaCurva_ConErrores
// Archivo:  FuncionesAuxiliares.cpp.cpp
//
// Autor:   J. Miguel Guanira E.
// Creado el sábado, 23 de Agosto del 2025 a las 20:14:54.
//

#include "FuncionesAuxiliares.h"

double evaluaLaFuncion(double x, double c5, double c4, double c3, double c2,
                      double c1, double c0){
    double resultado;
    resultado = c5*potencia(x,5) + c4*potencia(x,4) + c3*potencia(x,3) +
                c2*potencia(x,2) + c1*potencia(x,1) + c0*potencia(x,0);
    return resultado;
}

double potencia(double x, int n){
    double pot=1;
    for(int i=0; i<n; i++){
        pot *= x;
    }
    return pot;
}