//
// Created by Saymon on 9/15/26.
//

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
#include "funciones.h"

#define DIA_INI (6*3600)
#define DIA_FIN (17*3600+59*60+59)
#define T_SAFE_MIN 0
#define T_SAFE_MAX 90
#define V_SAFE_MIN 0
#define V_SAFE_MAX 15
#define LINE_SZ 62


void leeDatosEImprimeReportes(const char* fnLecturas, const char* fnRepEstadisticas, const char* fnRepAlertas) {
    // definimos las variables para el reporte de estadisticas
    int fechaIni = 0, fechaFin = 0, cantMedT = 0, cantMedV = 0, cantAlerT = 0, cantAlerV = 0, cantDia = 0, cantNoche = 0;
    double promT, minT = MAXFLOAT, maxT = -MAXFLOAT, promV, minV = MAXFLOAT, maxV = -MAXFLOAT;
    leerMedicionesEImprimirAlertas(fnLecturas, fnRepAlertas, fechaIni, fechaFin, cantMedT, cantMedV, cantAlerT,
        cantAlerV, cantDia, cantNoche, promT, minT, maxT, promV, minV, maxV);
    imprimirEstadisticas(fnRepEstadisticas, fechaIni, fechaFin, cantMedT, cantMedV, cantAlerT, cantAlerV,
        cantDia, cantNoche, promT, minT, maxT, promV, minV, maxV);
}

void leerMedicionesEImprimirAlertas(const char* fnArch, const char* fnRep, int& fechaIni, int& fechaFin, int& cantMedT,
    int& cantMedV, int& cantAlerT, int& cantAlerV, int& cantDia, int& cantNoche, double& promT, double& minT,
    double& maxT, double& promV, double& minV, double& maxV) {
    ifstream arch(fnArch, ios::in);
    if (not arch.is_open()) openError(fnArch);
    ofstream rep(fnRep, ios::out);
    if (not rep.is_open()) openError(fnRep);
    int dia, mes, anho, hh, mm, ss;
    char c, tipo;
    double valor;
    imprimirCabeceraAlertas(rep);
    while (true) {
        arch>>dia;
        if (arch.eof()) break;
        arch>>c>>mes>>c>>anho>>hh>>c>>mm>>c>>ss>>tipo;
        valor = hallarValorMedicion(arch);
        if (verAlertaYactualizarEstadisticas(anho*10000+mes*100+dia, hh*3600+mm*60+ss, tipo, valor, fechaIni, fechaFin, cantMedT, cantMedV,
            cantAlerT, cantAlerV, cantDia, cantNoche, promT, minT, maxT, promV, minV, maxV))
            imprimirAlerta(rep, dia, mes, anho, tipo, valor);
    }
}

void openError(const char* fn) {
    cout<<"Error al abrir el archivo: "<<fn<<endl;
    exit(1);
}

void imprimirCabeceraAlertas(ofstream& arch) {
    arch.precision(2);
    arch<<fixed<<"LISTADO DE ALERTAS - LECTURAS FUERA DE RANGO"<<endl;
    imprimeLinea(arch, '-');
    arch<<left<<setw(13)<<"Fecha"<<setw(6)<<"Tipo"<<setw(28)<<"Medicion"<<right<<setw(15)<<"Valor"<<endl;
    imprimeLinea(arch, '-');
}

void imprimeLinea(ofstream& arch, char c) {
    arch<<setfill(c)<<setw(LINE_SZ)<<c<<setfill(' ')<<endl;
}

double hallarValorMedicion(ifstream& arch) {
    int cantMed = 0;
    double med, sumaMed = 0;
    while (arch.get() != '\n') {
        arch>>med;
        sumaMed += med;
        cantMed++;
    }
    return sumaMed/cantMed; // siempre hay al menos 1 medicion
}

bool verAlertaYactualizarEstadisticas(int fecha, int hora, char tipo, double valor, int& fechaIni, int& fechaFin,
    int& cantMedT, int& cantMedV, int& cantAlerT, int& cantAlerV, int& cantDia, int& cantNoche, double& promT,
    double& minT, double& maxT, double& promV, double& minV, double& maxV) {
    // estadisticas del dia
    if (!fechaIni and !fechaFin) fechaIni = fechaFin = fecha;
    else if (fecha < fechaIni) fechaIni = fecha;
    else if (fecha > fechaFin) fechaFin = fecha;
    // estadisticas de la hora
    if (hora >= DIA_INI and hora <= DIA_FIN) cantDia++;
    else cantNoche++;
    // tipo, min, max, alertas
    if (tipo == 'T') {
        cantMedT++;
        promT += valor;
        if (valor < minT) minT = valor;
        if (valor > maxT) maxT = valor;
        if (valor<T_SAFE_MIN or valor>T_SAFE_MAX) {
            cantAlerT++;
            return true;
        }
    } else {
        cantMedV++;
        promV += valor;
        if (valor < minV) minV = valor;
        if (valor > maxV) maxV = valor;
        if (valor<V_SAFE_MIN or valor>V_SAFE_MAX) {
            cantAlerV++;
            return true;
        }
    }
    return false; // no hay alerta
}

void imprimirAlerta(ofstream& arch, int dia, int mes, int anho, char tipo, double valor) {
    arch<<setfill('0')<<setw(2)<<dia<<"/"<<setw(2)<<mes<<"/"<<anho<<setfill(' ')<<setw(3)<<" "<<left<<setw(6)<<tipo;
    if (tipo == 'T') arch<<setw(28)<<"Temperatura (C)";
    else arch<<setw(28)<<"Velocidad (mm/s)";
    arch<<right<<setw(15)<<valor<<endl;
}

void imprimirEstadisticas(const char* fn, int fechaIni, int fechaFin, int cantMedT, int cantMedV, int cantAlerT,
    int cantAlerV, int cantDia, int cantNoche, double promT, double minT, double maxT, double promV, double minV, double maxV) {
    ofstream arch(fn, ios::out);
    if (not arch.is_open()) openError(fn);
    arch.precision(2);
    arch<<fixed;
    imprimeLinea(arch, '=');
    arch<<"REPORTE DE MONITOREO DE SENSORES"<<endl;
    imprimeLinea(arch, '=');
    arch<<"Periodo del reporte: ";
    imprimeFecha(arch, fechaIni);
    arch<<" al ";
    imprimeFecha(arch, fechaFin);
    arch<<endl;
    imprimirTipoMedicion(arch, "TEMPERATURA (T)", "Temperatura (C)", cantMedT, cantAlerT, promT, minT, maxT);
    imprimirTipoMedicion(arch, "VIBRACION (V)", "Velocidad (mm/s)", cantMedV, cantAlerV, promV, minV, maxV);
    imprimeLinea(arch, '-');
    arch<<left<<"LECTURAS POR TURNO"<<endl;
    imprimeLinea(arch, '-');
    arch<<left<<setw(14)<<"Turno"<<right<<setw(10)<<"Lecturas"<<endl;
    arch<<left<<setw(14)<<"Dia"<<right<<setw(10)<<cantDia<<endl;
    arch<<left<<setw(14)<<"Noche"<<right<<setw(10)<<cantNoche<<endl;
    imprimeLinea(arch, '-');
    arch<<left<<"Total de alertas registradas en el periodo: "<<cantAlerT+cantAlerV<<endl;
    imprimeLinea(arch, '=');
}

void imprimeFecha(ofstream& arch, int fecha) {
    int anho = fecha/10000, mes = (fecha%10000)/100, dia = (fecha%10000)%100;
    arch<<right<<setfill('0')<<setw(2)<<dia<<"/"<<setw(2)<<mes<<"/"<<setw(4)<<anho<<setfill(' ');
}

void imprimirTipoMedicion(ofstream& arch, const char* tituloMed, const char* descripcionMed, int cantMed, int cantAler,
    double prom, double min, double max) {
    imprimeLinea(arch, '-');
    arch<<tituloMed<<"   -   "<<"Lecturas: "<<cantMed<<"   Alertas: "<<cantAler<<endl;
    arch<<left<<setw(22)<<"Medicion"<<right<<setw(12)<<"Promedio"<<setw(12)<<"Minimo"<<setw(12)<<"Maximo"<<endl;
    arch<<left<<setw(22)<<descripcionMed<<right<<setw(12)<<prom/cantMed<<setw(12)<<min<<setw(12)<<max<<endl;
}
