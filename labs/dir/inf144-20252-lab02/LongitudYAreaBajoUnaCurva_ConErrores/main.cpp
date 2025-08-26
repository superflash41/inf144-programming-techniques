/*
 * Archivo: main.cpp
 * Autor:   ***COLOQUE AQUÍ SU CÓDIGO, NOMBRE Y APELLIDO ***
 * Fecha y Hora: ***COLOQUE AQUÍ LA FECHA Y HORA EN LA QUE EMPEZÓ A ESCRIBIR ***
 *
 * ********************************************************************
 *
 *    Programa que calcula la longitud y el área bajo la curva de un
 *    intervalo dado, mediante aproximaciones sucesivas.
 *
 * ********************************************************************
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include <cmath>
#include "Bibliotecas/FuncionesAuxiliares.h"

//#define EXACTITUD 0.000001

int main(int argc, char** argv) {
    double c5, c4, c3, c2, c1, c0;
    double limiteInferior, limiteSuperior;
    double h, x1, x2, y1, y2;
    int numIntervalos, i;
    double area = 0.0, areaAnterior, longitud = 0.0, longitudAnterior;
    bool fin = false;
    double diferenciaAreas, diferenciaLongitudes;
    double exactitud;
    cout.precision(7);
    cout<<fixed;

    cout<<"Ingrese los coeficientes c5, c4, c3, c2, c1 y c0: ";
    cin >> c5>> c4 >> c3 >> c2 >> c1 >> c0;

    cout<<endl<<"Ingrese los limites inferior y superior: ";
    cin >> limiteInferior >> limiteSuperior;

    cout<<endl<<"Ingrese la exactitud: ";
    cin >> exactitud;


    cout<<endl<<left<<setw(18)<<"Intervalos"<<setw(20)<<"Area"
            <<setw(20)<<"Longitud"<<endl;
    while(not fin){
        areaAnterior = area;
        longitudAnterior = longitud;
        area = longitud = 0.0;
        numIntervalos++;
        h = (limiteSuperior - limiteInferior) / numIntervalos;
        x1 = limiteInferior;

        for(i = 1; i<=numIntervalos; i++){
            x2 = x1 + h;
            y1 = evaluaLaFuncion(x1, c5, c4, c3, c2, c1, c0);
            y2 = evaluaLaFuncion(x2, c5, c4, c3, c2, c1, c0);
            area += (y1 + y2)*h/2;
            longitud += sqrt( potencia(y2-y1,2) + potencia(h,2) );
            x1 = x2;
        }
        cout<<right<<setw(7)<<numIntervalos<<setw(20)<<area
                <<setw(20)<<longitud<<endl;
        diferenciaAreas = fabs(area-areaAnterior);
        diferenciaLongitudes = fabs(longitud-longitudAnterior);
        fin =  diferenciaAreas >= exactitud or
               diferenciaLongitudes >= exactitud;
    };

    cout<<endl;
    cout<<left<<setw(25)<<"Area bajo la curva ="<<right<<setw(10)<<area<<endl;
    cout<<left<<setw(25)<<"Longitud de la curva ="<<right<<setw(10)<<longitud<<endl;


    return 0;
}
