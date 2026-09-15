#include <iostream>
using namespace std;
#include "Bibliotecas/funciones.h"

#define LECTURAS "ArchivosDeDatos/lecturas_sensores_planta.txt"
#define REPORTE_ESTADISTICAS "ArchivosDeReporte/estadisticas_sensores.txt"
#define REPORTE_ALERTAS "ArchivosDeReporte/alertas_sensores.txt"

// 2026-2 INF144 - Laboratorio 02
// el objetivo de este programa es imprimir dos reportes relacionados a mediciones de
// de temperaturas y vibraciones. el primer reporte es de estadisticas y el segundo de alertas.

int main() {
    leeDatosEImprimeReportes(LECTURAS, REPORTE_ESTADISTICAS, REPORTE_ALERTAS);
    return 0;
}
