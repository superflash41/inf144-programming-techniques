//
// Created by sn on 10/2/25.
//

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
#include "funciones.h"

#define SZ_CANALES 120
#define SZ_ETIQUETAS 120
#define NOT_FOUND -1

// fn es filename
void leeDatosEImprimeReporte(const char* fnCanal, const char* fnEtiquetas, const char* fnCanEti,
    const char* fnRep) {
    // declaramos los arreglos necesarios (guiarse de las columnas del reporte)
    int fechas[SZ_CANALES], codN[SZ_CANALES], codE[SZ_ETIQUETAS], duracion[SZ_ETIQUETAS],
        cantRepC[SZ_CANALES]{}, tiempoRepC[SZ_CANALES]{}, ppr[SZ_CANALES], cantRepE[SZ_ETIQUETAS]{},
        tiempoRepE[SZ_ETIQUETAS]{}, numCanales = 0 , numEtiquetas = 0;
    char codC[SZ_CANALES];
    double rating[SZ_CANALES], ingresos[SZ_CANALES]{};
    double tarifa;
    cout<<"Ingrese la tarifa por duracion de la etiqueta: "; cin>>tarifa;
    // leemos los archivos Canales.txt y Etiquetas.txt
    leerCanales(fnCanal, fechas, codN, codC, rating, numCanales);
    leerEtiquetas(fnEtiquetas, codE, duracion, numEtiquetas);
    // imprimimos el reporte parcial
    imprimirReportePreliminar(fechas, codN, codC, rating, numCanales, codE, duracion, numEtiquetas);
    // actualizamos los arreglos vacios con el archivo ReproduccionesDeEtiquetas.txt
    actualizarArreglos(fnCanEti, codN, codC, codE, duracion,cantRepC, tiempoRepC, rating, ppr, cantRepE,
        tiempoRepE, ingresos, numCanales, numEtiquetas, tarifa);
    // imprimimos el reporte final
    imprimirReporteFinal(fnRep, fechas, codN, codC, rating, cantRepC, tiempoRepC, ppr, ingresos, numCanales,
        codE, duracion, cantRepE, tiempoRepE, numEtiquetas, tarifa);
}

void leerCanales(const char* fn, int* fechas, int* codN, char* codC, double* rating, int& numCanales) {
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    int dd, mm, aa;
    char c;
    while (true) {
        arch>>dd;
        if (arch.eof()) break;
        arch>>c>>mm>>c>>aa;
        fechas[numCanales] = aa*10000 + mm*100 + dd; // guardamos la fecha
        arch>>codC[numCanales]>>codN[numCanales]>>ws;
        while (arch.get() != ' '); // ignoramos el nombre del canal
        arch>>rating[numCanales++];
        while (arch.get() != '\n'); // saltamos a la siguiente linea
    }
}

void openError(const char* fn) {
    cout<<"Error al abrir el archivo: "<<fn<<endl;
    exit(1);
}

void leerEtiquetas(const char* fn, int* codE, int* duracion, int& numEtiquetas) {
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    int mm, ss;
    char c;
    while (true) {
        arch>>codE[numEtiquetas];
        if (arch.eof()) break;
        arch>>ws;
        while (arch.get() != ' '); // ignoramos el nombre de la etiqueta
        arch>>mm>>c>>ss;
        duracion[numEtiquetas++] = mm*60 + ss; // guardamos la duracion
    }
}

void imprimirReportePreliminar(int* fechas, int* codN, char* codC, double* rating, int numCanales,
    int* codE, int* duracion, int numEtiquetas) {
    ofstream arch("ArchivosDeReporte/ReportePreliminar.txt", ios::out);
    if (not arch.is_open()) openError("ReportePreliminar.txt");
    arch<<setw(50)<<"PLATAFORMA TP_Twitch"<<endl;
    imprimirCanalesPrelim(arch, fechas, codN, codC, rating, numCanales);
    imprimirEtiquetasPrelim(arch, codE, duracion, numEtiquetas);
}

void imprimirCanalesPrelim(ofstream& arch, int* fechas, int* codN, char* codC, double* rating, int nc) {
    imprimeLinea(arch, '=');
    arch<<"CANALES ADSCRITOS A LA PLATAFORMA"<<endl;
    imprimeLinea(arch, '-');
    arch<<setw(30)<<" "<<setw(14)<<"RATING DE"<<endl;
    arch<<"No."<<setw(10)<<"CODIGO"<<setw(20)<<"FECHA DE CREACION"<<setw(10)<<"CALIDAD"<<endl;
    for (int i=0; i<nc; i++)
        arch<<setfill(' ')<<setw(3)<<i+1<<")"<<setw(4)<<codC[i]<<codN[i]<<setw(6)<<" "<<
            setfill('0')<<setw(2)<<fechas[i]%100<<"/"<<setw(2)<<(fechas[i]%10000)/100<<
                "/"<<setw(4)<<fechas[i]/10000<<setfill(' ')<<setw(12)<<rating[i]<<endl;
}

void imprimeLinea(ofstream& arch, char c) {
    arch<<setfill(c)<<setw(130)<<c<<setfill(' ')<<endl;
}

void imprimirEtiquetasPrelim(ofstream& arch, int* codE, int* duracion, int ne) {
    imprimeLinea(arch, '=');
    arch<<"ETIQUETAS DE LA PLATAFORMA"<<endl;
    imprimeLinea(arch, '-');
    arch<<"No."<<setw(13)<<"ETIQUETA"<<setw(12)<<"DURACION"<<endl;
    for (int i=0; i<ne; i++)
        arch<<setfill(' ')<<setw(3)<<i+1<<")"<<setw(10)<<codE[i]<<setw(6)<<" "<<setfill('0')<<
            setw(2)<<duracion[i]/60<<":"<<setw(2)<<duracion[i]%60<<setfill(' ')<<endl;
}

void actualizarArreglos(const char* fn, int* codN, char* codC, int* codE, int* duracion, int* cantRepC,
    int* tiempoRepC, double* rating, int* ppr, int* cantRepE, int* tiempoRepE, double* ingresos,
    int nc, int ne, double tarifa) {
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    int n, codigoN, codigoE, cantRep, posCan, posEti;
    char c, codigoC;
    while (true) {
        arch>>n;
        if (arch.eof()) break;
        arch>>c>>n>>c>>n>>codigoC>>codigoN>>codigoE>>cantRep;
        if ((posCan=buscarCanal(codigoN, codigoC, codN, codC, nc)) != NOT_FOUND)
            actualizarCanal(codigoE, codE, duracion, ne, cantRep, cantRepC[posCan], tiempoRepC[posCan]);
        if ((posEti=buscarEtiqueta(codigoE, codE, ne)) != NOT_FOUND)
            actualizarEtiqueta(codigoN, codigoC, codN, codC, nc, cantRep, cantRepE[posEti],
                tiempoRepE[posEti], duracion[posEti]);
    }
    actualizarIngresos(tiempoRepC, rating, ppr, ingresos, nc, tarifa);
}

int buscarCanal(int codigoN, char codigoC, int* codN, char* codC, int nc) {
    for (int i=0; i<nc; i++)
        if (codigoC==codC[i] and codigoN==codN[i]) return i;
    return NOT_FOUND;
}

void actualizarCanal(int codigoE, int* codE, int* duracion, int ne, int cantRep, int& cantRepC,
    int& tiempoRepC) {
    cantRepC += cantRep;
    int posEti = buscarEtiqueta(codigoE, codE, ne);
    if (posEti != NOT_FOUND) tiempoRepC += cantRep*duracion[posEti];
}

int buscarEtiqueta(int codigoE, int* codE, int ne) {
    for (int i=0; i<ne; i++) if (codigoE==codE[i]) return i;
    return NOT_FOUND;
}

void actualizarEtiqueta(int codigoN, char codigoC, int* codN, char* codC, int nc, int cantRep,
    int& cantRepE, int& tiempoRepE, int duracion) {
    cantRepE += cantRep;
    int posCan = buscarCanal(codigoN, codigoC, codN, codC, nc);
    if (posCan != NOT_FOUND) tiempoRepE += cantRep*duracion;
}

void actualizarIngresos(int* tiempoRepC, double* rating, int* ppr, double* ingresos, int nc, double tarifa) {
    for (int i=0; i<nc; i++) {
        if (rating[i]<5 and rating[i]>4) ppr[i] = 30;
        else if (rating[i]>3) ppr[i] = 20;
        else if (rating[i]>2) ppr[i] = 0;
        else if (rating[i]>1) ppr[i] = -25;
        ingresos[i] = (tiempoRepC[i]/60.0)*(100+ppr[i])/100.0*tarifa;
    }
}

void imprimirReporteFinal(const char* fn, int* fechas, int* codN, char* codC, double* rating,
    int* cantRepC, int* tiempoRepC, int* ppr, double* ingresos, int nc, int* codE, int* duracion,
    int* cantRepE, int* tiempoRepE, int ne, double tarifa) {
    ofstream arch(fn, ios::out);
    if (not arch.is_open()) openError(fn);
    arch<<setprecision(2)<<fixed;
    arch<<setw(70)<<"PLATAFORMA TP_Twitch"<<endl;
    arch<<setw(50)<<"TARIFA POR DURACION DE LA ETIQUETAS: "<<tarifa<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimirCanalesFinal(arch, fechas, codN, codC, rating, cantRepC, tiempoRepC, ppr, ingresos, nc);
    imprimirEtiquetasFinal(arch, codE, duracion, cantRepE, tiempoRepE, ne);
}

void imprimirCanalesFinal(ofstream& arch, int* fechas, int* codN, char* codC, double* rating,
    int* cantRepC, int* tiempoRepC, int* ppr, double* ingresos, int nc) {
    imprimeLinea(arch, '=');
    arch<<"CANALES ADSCRITOS A LA PLATAFORMA"<<endl;
    imprimeLinea(arch, '-');
    arch<<setw(30)<<" "<<setw(14)<<"RATING DE"<<setw(20)<<"NUMERO TOTAL"<<setw(20)<<
        "TIEMPO TOTAL DE"<<setw(16)<<"POCENTAJE DE"<<setw(4)<<" "<<"INGRESOS POR REPRODUCCION"<<endl;
    arch<<"No."<<setw(10)<<"CODIGO"<<setw(20)<<"FECHA DE CREACION"<<setw(10)<<"CALIDAD"<<
        setw(22)<<"DE REPRODUCCIONES"<<setw(18)<<"REPRODUCCIONES"<<setw(20)<<"RATING DE CALIDAD"<<
            setw(16)<<"DE ETIQUETAS"<<endl;
    for (int i=0; i<nc; i++)
        arch<<setfill(' ')<<setw(3)<<i+1<<")"<<setw(4)<<codC[i]<<codN[i]<<setw(6)<<" "<<
            setfill('0')<<setw(2)<<fechas[i]%100<<"/"<<setw(2)<<(fechas[i]%10000)/100<<
                "/"<<setw(4)<<fechas[i]/10000<<setfill(' ')<<setw(12)<<rating[i]<<
                    setw(20)<<cantRepC[i]<<setw(10)<<" "<<setfill('0')<<
            setw(2)<<tiempoRepC[i]/3600<<":"<<setw(2)<<(tiempoRepC[i]%3600)/60<<":"<<
                setw(2)<<tiempoRepC[i]%60<<setfill(' ')<<setw(16)<<ppr[i]<<"%"<<
                        setw(20)<<ingresos[i]<<endl;
}

void imprimirEtiquetasFinal(ofstream& arch, int* codE, int* duracion, int* cantRepE, int* tiempoRepE, int ne) {
    imprimeLinea(arch, '=');
    arch<<"ETIQUETAS DE LA PLATAFORMA"<<endl;
    imprimeLinea(arch, '-');
    arch<<setw(30)<<" "<<setw(20)<<"CANTIDAD TOTAL"<<setw(20)<<"TIEMPO TOTAL DE"<<endl;
    arch<<"No."<<setw(13)<<"ETIQUETA"<<setw(12)<<"DURACION"<<setw(24)<<"DE REPRODUCCIONES"<<
        setw(16)<<"REPRODUCIDO"<<endl;
    for (int i=0; i<ne; i++)
        arch<<setfill(' ')<<setw(3)<<i+1<<")"<<setw(10)<<codE[i]<<setw(6)<<" "<<setfill('0')<<
            setw(2)<<duracion[i]/60<<":"<<setw(2)<<duracion[i]%60<<setfill(' ')<<
                setw(18)<<cantRepE[i]<<setw(12)<<" "<<setfill('0')<<
            setw(2)<<tiempoRepE[i]/3600<<":"<<setw(2)<<(tiempoRepE[i]%3600)/60<<":"<<
                setw(2)<<tiempoRepE[i]%60<<setfill(' ')<<endl;
}