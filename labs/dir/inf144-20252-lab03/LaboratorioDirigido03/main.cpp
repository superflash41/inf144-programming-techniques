#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
#include "Bibliotecas/FuncionesMatematicas.h"

#define PI 3.14159265

// 2025-2 INF144 - Laboratorio 03

int main() {

    cout<<setprecision(4)<<fixed; // para el formato de los decimales

    ////////////////////////// parte uno
    cout<<setw(10)<<" "<<setw(16)<<"biblioteca"<<setw(16)<<"cmath"<<endl;
    cout<<setw(10)<<"pi: "<<setw(16)<<pi(0.0001)<<setw(16)<<PI<<endl;
    cout<<setw(10)<<"seno: "<<setw(16)<<seno(0.001, 90.0*PI/180.0)<<setw(16)<<sin(90.0*PI/180.0)<<endl;
    cout<<setw(10)<<"coseno: "<<setw(16)<<coseno(0.001, PI)<<setw(16)<<cos(PI)<<endl;
    cout<<setw(10)<<"exp: "<<setw(16)<<exponencial(0.001, 5)<<setw(16)<<exp(5)<<endl;
    cout<<setw(10)<<"log: "<<setw(16)<<logaritmo(0.0001, 1.98)<<setw(16)<<log(1.98)<<endl;

    ////////////////////////// parte dos
    double p, x;
    char c;
    while (true) {
        cin>>c;
        if (c == 'P') {
            cin>>p;
            cout<<"valor de pi: "<<pi(p)<<endl;
        } else if (c == 'S') {
            cin>>c; // G o R
            cin>>p>>x;
            if (c == 'G') x *= PI/180.0; // convertimos a radianes
            cout<<"valor de seno: "<<seno(p,x)<<endl;
        } else if (c == 'C') {
            cin>>p>>x;
            if (c == 'G') x *= PI/180.0; // convertimos a radianes
            cout<<"valor de coseno: "<<coseno(p,x)<<endl;
        } else if (c == 'E') {
            cin>>p>>x;
            cout<<"valor de la exponencial: "<<exponencial(p,x)<<endl;
        } else if (c == 'L') {
            cin>>p>>x;
            cout<<"valor del logaritmo: "<<logaritmo(p,x)<<endl;
        } else if (c == 'F') return 0;
    }
}