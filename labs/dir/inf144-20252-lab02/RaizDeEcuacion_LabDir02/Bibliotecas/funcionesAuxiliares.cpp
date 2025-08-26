/*
* Proyecto:  RaizDeEcuacion
 * Archivo:   funcionesAuxiliares.cpp
 * Autor:     Ana Cecilia Roncal Neyra
 * Fecha:     Marzo del 2023
 */

#include <iostream>
using namespace std;
#include <cmath>
#define CUENTA_MAXIMA 100
#include "funcionesAuxiliares.h"

double calcularFx(double x, double coef4, double coef3,double coef2,
                  double coef1, double coef0){
    double fx;

    fx =  coef4 * calcularPotencia(x,4) + coef3 * calcularPotencia(x,3) +
          coef2 * calcularPotencia(x,2) + coef1 * x + coef0;
    return fx;
}

void solucionarProblema(double epsilon, double x1, double x2, double coef4,
        double coef3, double coef2, double coef1, double coef0, double fx1,
        double fx2){

    int cuenta;
    bool raizEncontrada;
    double x3, funcion3;

    cout<<"Ingresar la exactitud deseada: "<<endl;
    cin>>epsilon;
    raizEncontrada = false;
    cuenta = 0;
    while (not raizEncontrada and (cuenta <= CUENTA_MAXIMA)){

        x3 = (x2 * fx1 - x1 * fx2)/(fx1 - fx2);
        funcion3 = calcularFx(x3, coef4, coef3, coef2, coef1, coef0);
        cout<<"cuenta= "<<cuenta<<"  x1= "<<x1<<"   x3= "<<x3<<endl;
        if (fabs(funcion3)<epsilon)
            raizEncontrada = true;
        if (((fx1 <= 0.0) and (funcion3 <= 0.0)) or
                 ((fx1 >= 0.0) and (funcion3 >= 0.0))){
            x1 = x3 ;
            fx1 = funcion3;
                 }
        else{
            x2 = x3;
            fx2 = funcion3;
        }
        cuenta += 1;
        if (fabs(funcion3)<epsilon)
            raizEncontrada = true;
    }

    if (raizEncontrada)
        cout<<"La raiz es "<< x3 <<", con una exactitud de "
            <<epsilon<<endl;
    else
        cout<<"Lo sentimos, no pudimos encontrar la raiz en "
            <<CUENTA_MAXIMA<<" iteraciones"<<endl;
}

double calcularPotencia(double x, int n){
    double potencia = 1.0;
    int i;
    for(i=0; i < n; i++)
        potencia *= x;
    return potencia;
}
