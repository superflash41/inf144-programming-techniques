/*
* Proyecto:  RaizDeEcuacion
 * Archivo:   main.cpp
 * Autor:     Ana Cecilia Roncal Neyra
 * Fecha:     Marzo del 2023
 *
 *=============================================================================
 * Programa para encontrar la raíz de una ecuación empleando el método
 * de la Posición falsa, ejercicio adaptado del libro de (Schneider et al.,1986)
 *=============================================================================
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "Bibliotecas/funcionesAuxiliares.h"

int main(int argc, char** argv) {

    double coef4, coef3, coef2, coef1, coef0;
    double x1, x2;
    double epsilon;
    double fx1, fx2;
    bool darsePorVencido, datosBuenos;

    datosBuenos = false;
    darsePorVencido = false;

    while(not datosBuenos and not darsePorVencido){
        cout<<"Ingresar los dos puntos de inicio: "<<endl;
        cin>>x1>>x2;
        if((x1 == 0) and (x2 == 0)){
            darsePorVencido = true;
        }
        else{
            cout<<"Ingresar los coeficientes (del c4 al c0): "<<endl;
            cin>>coef4>>coef3>>coef2>>coef1>>coef0;
            fx1 = calcularFx(x1, coef4, coef3, coef2, coef1, coef0);
            fx2 = calcularFx(x2, coef4, coef3, coef2, coef1, coef0);
            if((fx1 <= 0.0 and fx2 >= 0.0) or
               (fx1 >= 0.0 and fx2 <= 0.0)) {
                datosBuenos = true;
               }
            else {
                cout<<"Lo siento, los puntos dados no estan opuestos"<<endl;
                cout<<"Ingresar 0,0 para terminar (puntos de inicio)"<<endl;
            }
        }
    }
    if (darsePorVencido){
        cout<<"Lo siento, el programa se concluye por una falla"<<endl;
        cout<<"para encontrar un intervalo inicial valido"<<endl;
    }
    else{
        solucionarProblema(epsilon, x1, x2, coef4, coef3, coef2, coef1, coef0,
                           fx1, fx2);
    }
    return 0;
}
