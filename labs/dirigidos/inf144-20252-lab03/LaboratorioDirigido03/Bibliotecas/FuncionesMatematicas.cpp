//
// Created by sn on 9/2/25.
//
#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesMatematicas.h"

// funcion que calcula el valor de pi como una productoria
// el parametro p se refiere a la precision
double pi(double p) {
    double anterior, producto = 2;
    int i = 1, num = 0, den = 1;
    while (true) {
        if (i%2) // en una iteracion impar
            num += 2;
        else // en una iteracion par
            den += 2;
        producto *= 1.0 * num / den; // calculo de pi
        if (i>1 and abs(anterior-producto)<p) return producto;
        anterior = producto; // actualizamos el valor para la siguiente iteracion
        i++;
    }
}

// funcion que calcula el seno con la serie de taylor
// el parametro p se refiere a la precision y x al angulo
double seno(double p, double x) {
    double suma = 0, num = x, anterior, factorial = 1;
    int i = 1;
    while (true) {
        if (i%2) // si es una iteracion impar
            suma += num/factorial;
        else // si es una iteracion par
            suma -= num/factorial;
        factorial *= (2*i)*(2*i+1);
        num *= x*x;
        if (i>1 and abs(anterior-suma)<p) return suma;
        anterior = suma; // actualizamos el valor para la siguiente iteracion
        i++;
    }
}

// funcion que calcula el coseno con la serie de taylor
// el parametro p se refiere a la precision y x al angulo
double coseno(double p, double x) {
    double suma = 0, num = 1, anterior, factorial = 1;
    int i = 1;
    while (true) {
        if (i%2) // si es una iteracion impar
            suma += num/factorial;
        else // si es una iteracion par
            suma -= num/factorial;
        factorial *= (2*i)*(2*i-1);
        num *= x*x;
        if (i>1 and abs(anterior-suma)<p) return suma;
        anterior = suma; // actualizamos el valor para la siguiente iteracion
        i++;
    }
}

// funcion que calcula la funcion exponencial
// el parametro p se refiere a la precision y x al exponente
double exponencial(double p, double x) {
    double suma = 0, num = 1, anterior, factorial = 1;
    int i = 1;
    while (true) {
        suma += num/factorial;
        num *= x;
        factorial *= i;
        if (i>1 and abs(anterior-suma)<p) return suma;
        anterior = suma; // actualizamos el valor para la siguiente iteracion
        i++;
    }
}

// funcion que calcula el logaritmo neperiano
// el parametro p es la precision y x la variable
double logaritmo(double p, double x) {
    double suma = 0, termino = 1, anterior;
    int i = 1;
    while (true) {
        termino *= (x-1)/x;
        suma += termino/i;
        if (i>1 and abs(anterior-suma)<p) return suma;
        anterior = suma; // actualizamos el valor para la siguiente iteracion
        i++;
    }
}