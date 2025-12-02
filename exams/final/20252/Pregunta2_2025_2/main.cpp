#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

#include "Bibliotecas/funciones.h"

#define STOPSWORDS "ArchivosDeDatos/stopwords.txt"
#define COMENTARIOS "ArchivosDeDatos/comentarios.csv"
#define R_STOPSWORDS "ArchivosDeReporte/ReporteStopsWords.txt"
#define R_COMENTARIOS "ArchivosDeReporte/ReportePalabras.txt"
#define R_FRECUENCIA "ArchivosDeReporte/palabras_frecuencia.txt"
#define R_PALABRAS_FRECUENTES "ArchivosDeReporte/reporte_palabras_frecuentes.txt"

// nah, I'd win

int main() {
    resolverPreguntaDos(STOPSWORDS, COMENTARIOS,
        R_STOPSWORDS, R_COMENTARIOS, R_FRECUENCIA, R_PALABRAS_FRECUENTES);
    return 0;
}