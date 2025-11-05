#include <iostream>
#include <iomanip>
using namespace std;
#include "Bibliotecas/funciones.h"

// 2025-2 INF144 - Laboratorio 01
// el objetivo de este programa es imprimir un reporte
// sobre canales de la plataforma TP_Twitch y sus ultimos streams

int main() {
    cout<<setprecision(2)<<fixed; // para el formato de los decimales
    // es recomendable poner la menor cantidad de codigo en el main
    // asi aprovechamos la idea de "modularidad" (usar modulos)
    leeDatosEImprimeReporte();
    return 0;
}