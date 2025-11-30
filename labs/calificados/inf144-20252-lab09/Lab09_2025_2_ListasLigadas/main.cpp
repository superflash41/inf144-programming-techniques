#include <iostream>
using namespace std;
#include "Bibliotecas/funciones.h"

#define STREAMS "ArchivosDeDatos/StreamsReproducidos.csv"
#define CATEGORIAS "ArchivosDeDatos/Categorias.csv"
#define REPORTE_PRUEBA "ArchivosDeReporte/ReporteDePruebaDeCategorias.txt"
#define REPORTE_COMPLETO "ArchivosDeReporte/ReporteDeCategoriasCompleto.txt"
#define REPORTE_ELIMINADO "ArchivosDeReporte/ReporteDeCategoriasEliminados.txt"

// 2025-2 INF144 - Laboratorio 09
// el objetivo de este programa es imprimir reportes sobre categorías de streams
// haciendo el uso exacto de memoria al trabajar con la estructura de dato de lista se
// imprimirá un reporte de prueba de lectura, uno con información de los streams que se
// reprodujeron por categoría y uno donde se filtren categorías basadas en el drop-off

int main() {
    leeDatosEImprimeReporte(CATEGORIAS, STREAMS, REPORTE_PRUEBA, REPORTE_COMPLETO, REPORTE_ELIMINADO);
    // navidad se acerca!
    return 0;
}