#include <iostream>
#include <iomanip>
using namespace std;
#include "Bibliotecas/funcionesAuxiliares.h"

// 2024-1 INF144 - Laboratorio 01
// el objetivo del laboratorio es practicar el redireccionamiento de datos
// el comando para hacerlo es:
// EntradaYSalidaDeDatosLab01-2024-1.exe<ArchivosDeDatos\CitasMedicas.txt>ArchivosDeReporte\Reporte.txt

int main() {

    cout<<setprecision(2)<<fixed; // para el formato de los decimales

    // es recomendable poner la menor cantidad de codigo en el main
    // asi aprovechamos la idea de "modularidad" (usar modulos)
    leeDatosEImprimeReporte();

    return 0;
}