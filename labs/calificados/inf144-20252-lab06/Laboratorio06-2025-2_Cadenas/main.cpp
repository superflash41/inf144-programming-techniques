#include <iostream>
using namespace std;
#include "Bibliotecas/funciones.h"

#define STREAMS "ArchivosDeDatos/StreamsReproducidos.txt"
#define CATEGORIAS "ArchivosDeDatos/Categorias.txt"
#define REPORTE "ArchivosDeReporte/"

// 2025-2 INF144 - Laboratorio 06
// el objetivo de este programa es imprimir múltiples reportes por categoría
// cada uno debe contener información de los streams reproducidos para esa categoría
// se trabajarán con cadenas de caracteres para los nombres de canales y categorias

int main() {
    // nah, I'd win...
    leeDatosEImprimeReporte(CATEGORIAS, STREAMS, REPORTE);
    return 0;
}
