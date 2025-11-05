#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "funciones.h"

#define SZ_CATEGORIAS 200
#define SZ_STREAMS 500
#define NOT_FOUND -1

// fn es filename
// dir es la carpeta donde deben ir los reportes
void leeDatosEImprimeReporte(const char* fnCategorias, const char* fnStreams, const char* dirRep) {
    // declaramos los arreglos para los streams(usa arr como prefijo para que no te bajen nota :V)
    int arrFecha[SZ_STREAMS], arrDuracion[SZ_STREAMS], numStreams = 0;
    char* arrNombreCanal[SZ_STREAMS]{}, *arrCodCateStream[SZ_STREAMS]{};
    double arrRating[SZ_STREAMS], arrDropOff[SZ_STREAMS];
    // declaramos los arreglos para las categorias
    int numCategorias = 0;
    char* arrCodCategoria[SZ_CATEGORIAS]{}, *arrNombreCategoria[SZ_CATEGORIAS]{};
    leerCategorias(fnCategorias, arrCodCategoria, arrNombreCategoria, numCategorias);
    emitirReportePruebaCategorias(reporteDePrueba(dirRep, "Categorias"), arrCodCategoria, arrNombreCategoria, numCategorias);
    leerStreams(fnStreams, arrFecha, arrNombreCanal, arrCodCateStream, arrRating, arrDropOff, arrDuracion, numStreams);
    emitirReportePruebaStreams(reporteDePrueba(dirRep, "StreamsReproducidos"), arrFecha, arrNombreCanal, arrCodCateStream,
        arrRating, arrDropOff, arrDuracion, numStreams);
    imprimirReportes(dirRep, arrCodCategoria, arrNombreCategoria, numCategorias, arrFecha, arrNombreCanal,
        arrCodCateStream, arrRating, arrDropOff, arrDuracion, numStreams);
}

void leerCategorias(const char* fn, char** arrCodCategoria, char** arrNombreCategoria, int& nc) {
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    while (true) {
        arrCodCategoria[nc] = leerCadenaExacta(arch, ' ');
        if (not arrCodCategoria[nc]) break;
        arch>>ws;
        arrNombreCategoria[nc++] = leerCadenaExacta(arch, '\r'); // i use '\r' because i am on linux TT
        arch>>ws;
    }
}

void openError(const char* fn) {
    cout<<"Error al abrir el archivo: "<<fn<<endl;
    exit(1);
}

char* leerCadenaExacta(ifstream& arch, char c) {
    char s[100];
    arch.getline(s, 100, c);
    if (arch.eof()) return nullptr;
    char* pt = new char[strlen(s)+1]{};
    strcpy(pt, s);
    return pt;
}

// solo hice esta funcion por diversion
// para probar concatenar muchas cadenas (ahi puse un ejemplo de como funciona)
char* reporteDePrueba(const char* dir, const char* fn) {
    char s[200]{};
    strcpy(s, dir);                     // "ArchivosDeReporte/"
    strcat(s, "ReporteDePruebaDe"); // "ArchivosDeReporte/ReporteDePruebaDe"
    strcat(s, fn);                      // "ArchivosDeReporte/ReporteDePruebaDeCategorias"
    strcat(s, ".txt");              // "ArchivosDeReporte/ReporteDePruebaDeCategorias.txt"
    char* pt = new char[strlen(s)+1]{};
    strcpy(pt, s);
    return pt;
}

void emitirReportePruebaCategorias(const char* fn, char** arrCodCategoria, char** arrNombreCategoria, int nc) {
    ofstream arch(fn, ios::out);
    if (not arch.is_open()) openError(fn);
    arch<<setw(30)<<"REPORTE DE PRUEBA DE CATEGORIAS"<<endl;
    arch<<"CODIGO"<<setw(20)<<"NOMBRE"<<endl;
    for (int i=0; i<nc; i++) arch<<left<<setw(20)<<arrCodCategoria[i]<<setw(50)<<arrNombreCategoria[i];
}

void leerStreams(const char* fn, int* arrFecha, char** arrNombreCanal, char** arrCodCateStream, double* arrRating,
    double* arrDropOff, int* arrDuracion, int& ns) {
    int dd, mm, aa, hora, min, seg;
    char c;
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    while (true) {
        arch>>dd;
        if (arch.eof()) break;
        arch>>c>>mm>>c>>aa>>ws;
        arrFecha[ns] = convert(aa, mm, dd, 'd');
        arrNombreCanal[ns] = leerCadenaExacta(arch, ' ');
        arch>>ws;
        arrCodCateStream[ns] = leerCadenaExacta(arch, ' ');
        arch>>arrRating[ns]>>arrDropOff[ns]>>hora>>c>>min>>c>>seg;
        arrDuracion[ns++] = convert(hora, min, seg, 'h');
    }
}

// funcion para convertir valores a una fecha o a una hora ('d' o 'h')
int convert(int a, int b, int c, char o) {
    if (o=='d') return a*10000+b*100+c; // date
    return a*3600+b*60+c; // time
}

void emitirReportePruebaStreams(const char* fn, int* arrFecha, char** arrNombreCanal, char** arrCodCateStream,
        double* arrRating, double* arrDropOff, int* arrDuracion, int ns) {
    ofstream arch(fn, ios::out);
    if (not arch.is_open()) openError(fn);
    arch<<setprecision(2)<<fixed;
    arch<<setw(50)<<"REPORTE DE PRUEBA DE STREAMS"<<endl;
    arch<<setw(8)<<"FECHA"<<setw(26)<<"NOMBRE DEL CANAL"<<setw(36)<<"CODIGO DE LA CATEGORIA"<<
        setw(12)<<"RATING"<<setw(12)<<"DROP OFF"<<setw(14)<<"DURACION"<<endl;
    for (int i=0; i<ns; i++) {
        int hora = arrDuracion[i]/3600, min = (arrDuracion[i]%3600)/60, seg = (arrDuracion[i]%3600)%60;
        int aa = arrFecha[i]/10000, mm = (arrFecha[i]%10000)/100, dd = arrFecha[i]%100;
        arch<<right<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<
            setfill(' ')<<left<<setw(6)<<" "<<setw(40)<<arrNombreCanal[i]<<setw(20)<<arrCodCateStream[i]<<
                setw(10)<<arrRating[i]<<setw(10)<<arrDropOff[i]<<setw(4)<<" "<<right<<
                    setfill('0')<<hora<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<left<<endl;
    }
}

void imprimirReportes(const char* dirRep, char** arrCodCategoria, char** arrNombreCategoria, int nc,
    int* arrFecha, char** arrNombreCanal, char** arrCodCateStream, double* arrRating, double* arrDropOff,
    int* arrDuracion, int ns) {
    // por cada categoria generamos su nombre de reporte, enlace, e imprimimos sus streams
    for (int i=0; i<nc; i++) {
        char* fnRep, *enlace;
        generaArchivoEnlace(arrNombreCategoria[i], fnRep, enlace);
        imprimirReporteCategoria(fnRep, enlace, arrCodCategoria[i], arrNombreCategoria[i], arrFecha, arrNombreCanal,
            arrCodCateStream, arrRating, arrDropOff, arrDuracion, ns);
    }
}

void generaArchivoEnlace(const char* categoria, char*& nombArch, char*& enlace) {
    char nombre[200]{}, url[200]{}, *categoriaFormat = format(categoria);
    // formateamos el nombre
    strcpy(nombre, "ArchivosDeReporte/");  // "ArchivosDeReporte/"
    strcat(nombre, categoriaFormat);           // "ArchivosDeReporte/Categoria"
    strcat(nombre, ".txt");                // "ArchivosDeReporte/Categoria.txt"
    strcpy(url, "https://Laboratorio06_2025_2/ArchivosDeReporte/");
    strcat(url, categoriaFormat);           // "https://Laboratorio06_2025_2/ArchivosDeReporte/Categoria"
    nombArch = new char[strlen(nombre)+1]{};
    strcpy(nombArch, nombre);
    enlace = new char[strlen(url)+1]{};
    strcpy(enlace, url);
}

// formatea un string (xxx_yyy_zzz -> Xxx_Yyy_Zzz)
char* format(const char* s) {
    char* formateada = new char[strlen(s)+1]{};
    strcpy(formateada, s);
    for (int i=0; formateada[i]; i++)
        if (i==0 or (i>0 and formateada[i-1]=='_'))
            formateada[i] -= (formateada[i]>='a' and formateada[i]<='z') ? 'a' - 'A' : 0;
    return formateada;
}

void imprimirReporteCategoria(const char* fnRep, const char* enlace, const char* codCategoria,
    const char* nombreCategoria, int* arrFecha, char** arrNombreCanal, char** arrCodCateStream,
    double* arrRating, double* arrDropOff, int* arrDuracion, int ns) {
    ofstream arch(fnRep, ios::out);
    if (not arch.is_open()) openError(fnRep);
    arch<<setprecision(2)<<fixed;
    imprimirCabecera(arch, codCategoria, nombreCategoria, enlace);
    int dd, mm, aa, hora, min, seg, numStreamsCategoria = 0, sumaDuracion = 0;
    double sumaRating = 0, sumaDropOff = 0;
    // vemos cada stream a ver si tiene el codigo de la cetegoria
    for (int i=0; i<ns; i++)
        if (strcmp(arrCodCateStream[i], codCategoria)==0) {
            hora = arrDuracion[i]/3600; min = (arrDuracion[i]%3600)/60; seg = (arrDuracion[i]%3600)%60;
            aa = arrFecha[i]/10000; mm = (arrFecha[i]%10000)/100; dd = arrFecha[i]%100;
            numStreamsCategoria++; sumaDuracion += arrDuracion[i];
            sumaRating += arrRating[i]; sumaDropOff += arrDropOff[i];
            arch<<right<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<
            setfill(' ')<<left<<setw(6)<<" "<<setw(50)<<arrNombreCanal[i]<<setw(10)<<arrRating[i]<<
                setw(10)<<arrDropOff[i]<<setw(4)<<" "<<right<<setfill('0')<<hora<<":"<<
                    setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<left<<endl;
        }
    imprimirResumen(arch, numStreamsCategoria ? sumaRating/numStreamsCategoria : 0,
        numStreamsCategoria ? sumaDropOff/numStreamsCategoria : 0, sumaDuracion);
}

void imprimirCabecera(ofstream& arch, const char* codigo, const char* nombre, const char* enlace) {
    arch<<"Codigo: "<<codigo<<endl;
    arch<<"Nombre: "<<nombre<<endl;
    arch<<"Enlace: "<<enlace<<endl;
    arch<<"REPRODUCCIONES: "<<endl;
    imprimeLinea(arch, '=');
    arch<<"FECHA"<<setw(20)<<"CANAL"<<setw(46)<<"RATING"<<setw(12)<<"DROP-OFF"<<setw(14)<<"DURACION"<<endl;
}

void imprimeLinea(ofstream& arch, char c) {
    arch<<setfill(c)<<setw(100)<<c<<setfill(' ')<<endl;
}

void imprimirResumen(ofstream& arch, double promRating, double promDropOff, int sumaDuracion) {
    int hora = sumaDuracion/3600, min = (sumaDuracion%3600)/60, seg = (sumaDuracion%3600)%60;
    imprimeLinea(arch, '=');
    arch<<left<<setw(30)<<"PROMEDIO DE RATING: "<<right<<setw(8)<<promRating<<endl;
    arch<<left<<setw(30)<<"PROMEDIO DE DROP-OFF: "<<right<<setw(8)<<promDropOff<<endl;
    arch<<left<<setw(30)<<"DURACION TOTAL: "<<right<<setw(4)<<" "<<right<<setfill('0')<<
        hora<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<left<<endl;
}