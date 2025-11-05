#include <iostream>
using namespace std;
#include "Bibliotecas/funciones.h"

#define CANALES "ArchivosDeDatos/Canales.txt"
#define ETIQUETAS "ArchivosDeDatos/Etiquetas.txt"
#define CANAL_ETIQUETAS "ArchivosDeDatos/ReproduccionesDeEtiquetas.txt"
#define REPORTE "ArchivosDeReporte/ReporteFinal.txt"

// 2025-2 INF144 - Laboratorio 04
// el objetivo de este programa es imprimir un reporte
// sobre canales y etiquetas haciendo uso de arreglos

int main() {
    leeDatosEImprimeReporte(CANALES, ETIQUETAS, CANAL_ETIQUETAS, REPORTE);
    // nota: faltan corregir algunas cosas del alineado en el reporte
    return 0;
}
