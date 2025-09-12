//
// Created by sn on 9/12/25.
//

#include <iostream>
#include <iomanip>
using namespace std;
#include "funciones.h"

// estructura de los datos que seran leidos
// dia/mes/anho   codigo  nombre  numSeguidores  [diaS/mesS/anhoS  hh:mm:ss   vistas]...

// funcion que lee e imprime al mismo tiempo informacion relacionada con los canales
// al final se imprime un resumen
void leeDatosEImprimeReporte(void) {
    // variables para leer los datos
    int dd, mm, aa, date, codeNum;
    char codeChar, c; // cualquier caracter
    // variables adicionales para el reporte final
    int streams = 0, duracionTotal = 0, codeNumM;
    char codeCharM;
    double ingresosTotal = 0, ingresoM = -1.0; // codeNumM, codeCharM y ingresoM son para el canal con mayor ingreso
    imprimirEncabezadoReporte();
    for (int i=1; ;) {
        cin>>dd;
        if (cin.eof()) break;
        cin>>c>>mm>>c>>aa;
        date = convert(aa, mm, dd, 'd');
        if (date >= 20220909 and date <= 20230101) {
            imprimirEncabezadoCanal(aa, mm, dd, i, codeNum, codeChar);
            imprimirUltimosStreams(codeNum, codeChar, streams, duracionTotal, codeNumM, codeCharM, ingresosTotal, ingresoM);
            i++;
        } else while (cin.get() != '\n');
    }
    imprimirResumenFinal(streams, duracionTotal, ingresosTotal, codeCharM, codeNumM, ingresoM);
}

// funcion para imprimir el encabezado del reporte y los titulos de las columnas
void imprimirEncabezadoReporte(void) {
    cout<<setw(50)<<"PLATAFORMA TP_Twitch"<<endl;
    cout<<setw(60)<<"REGISTRO DE LOS CANALES AFILIADOS"<<endl;
    cout<<setw(70)<<"FECHAS DE CREACION ENTRE EL 09/09/2022 Y EL 01/01/2023"<<endl;
}

// funcion que imprime una linea para el reporte dado un caracter
void imprimeLinea(char c) {
    cout<<setfill(c)<<setw(90)<<c<<setfill(' ')<<endl;
}

// funcion para convertir valores a una fecha o a una hora
int convert(int a, int b, int c, char o) {
    if (o=='d') return a*10000+b*100+c; // date
    return a*3600+b*60+c; // time
}

// funcion para imprimir el encabezado de un canal y datos basicos: nombre, codigo, creacion y fc
void imprimirEncabezadoCanal(int aa, int mm, int dd, int i, int& codeNum, char& codeChar) {
    // variables para la lectura
    int fCount, empty = 20; // fcount: follower count
    char c;
    // encabezado del canal
    imprimeLinea('=');
    cout<<"CANAL No. "<<i<<endl;
    cout<<left<<setw(4)<<" "<<setw(20)<<"NOMBRE"<<setw(10)<<"CODIGO"<<setw(14)<<"CREADO EL"<<
        setw(20)<<"NUMERO DE SEGUIDORES"<<endl<<setw(4)<<" ";
    // lectura del codigo
    cin>>ws>>codeChar>>codeNum>>ws;
    // lectura e impresion del nombre
    while ((c=cin.get()) != ' ') {
        cout.put((c>='a' and c<='z') ? c-'a'+'A' : c);
        empty--; // menos espacios en blanco para dejar
    }
    // impresion del codigo, y fecha de creacion
    cout<<setw(empty)<<" "<<codeChar<<codeNum<<setw(5)<<" "<<right<<setfill('0')<<
        setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<left<<setw(4)<<" ";
    // lectura e impresion del numero de seguidores
    cin>>fCount; cout<<setw(10)<<fCount<<endl;
    imprimeLinea('-');
}

// funcion para imprimir informacion de los streams

void imprimirUltimosStreams(int codeNum, char codeChar, int& streams, int& duracionTotal, int& codeNumM,
    char& codeCharM, double& ingresosTotal, double& ingresoM) {
    // variables para la lectura
    int dd, mm, aa, date, hh, min, ss, vCount; // vCount: view count
    char c;
    // variables adicionales para el reporte del canal
    int duracion = 0, ultimaFecha = 0, total = 0, ingreso;
    cout<<setw(4)<<" "<<"ULTIMAS REPRODUCCIONES"<<endl;
    cout<<setw(8)<<" "<<setw(24)<<"FECHA DE PUBLICACION"<<setw(24)<<"TIEMPO DE DURACION"<<
        "NUMERO DE REPRODUCCIONES"<<endl;
    while (true) {
        if ((c=cin.get())=='\n' or c=='\r') break; // yo uso '\r' porque estoy en Linux
        cin>>dd>>c>>mm>>c>>aa>>hh>>c>>min>>c>>ss>>vCount;
        cout<<right<<setw(8)<<" "<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<
            setw(14)<<" "<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<ss<<setfill(' ')<<
                setw(16)<<" "<<setw(10)<<vCount<<left<<endl;
        // actualizacion de variables para el reporte del canal
        duracion += convert(hh, min, ss, 't');
        total += vCount;
        date = convert(aa, mm, dd, 'd');
        if (!ultimaFecha or date>ultimaFecha) ultimaFecha = date;
        streams++; // actualizacion del contador de streams para el reporte final
    }
    // actualizacion de variables para el reporte final
    duracionTotal += duracion;
    ingreso = 3.25*(total/1000.0);
    ingresosTotal += ingreso;
    if (ingresoM < 0 or ingresoM < ingreso) {
        ingresoM = ingreso;
        codeCharM = codeChar;
        codeNumM = codeNum;
    }
    imprimirResumenCanal(duracion, ultimaFecha, total, ingreso);
}

void imprimirResumenCanal(int duracion, int ultimaFecha, int total, double ingreso) {
    int hh = duracion/3600, min = (duracion%3600)/60, ss = (duracion%3600)%60;
    int aa = ultimaFecha/10000, mm = (ultimaFecha%10000)/100, dd = ultimaFecha%100;
    imprimeLinea('-');
    cout<<setw(8)<<"RESUMEN DEL CANAL"<<endl;
    cout<<setw(8)<<" "<<setw(40)<<"DURACION TOTAL DE LAS REPRODUCCIONES: "<<right<<
        setfill('0')<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<ss<<setfill(' ')<<left<<endl;
    cout<<setw(8)<<" "<<setw(40)<<"ULTIMA PUBLICACION: "<<right<<
        setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<left<<endl;
    cout<<setw(8)<<" "<<setw(40)<<"TOTAL DE REPRODUCCIONES: "<<setw(10)<<total<<endl;
    cout<<setw(8)<<" "<<setw(40)<<"INGRESOS POR PUBLICIDAD: "<<"$ "<<setw(10)<<ingreso<<endl;
}

void imprimirResumenFinal(int streams, int duracionTotal, double ingresosTotal, char codeCharM, int codeNumM,
    double ingresoM) {
    int hh = duracionTotal/3600, min = (duracionTotal%3600)/60, ss = (duracionTotal%3600)%60;
    imprimeLinea('=');
    cout<<"RESUMEN FINAL"<<endl;
    cout<<setw(60)<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES: "<<setw(10)<<streams<<endl;
    cout<<setw(60)<<"DURACION TOTAL DE STREAMS PUBLICADOS: "<<right<<
        setfill('0')<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<ss<<setfill(' ')<<left<<endl;
    cout<<setw(60)<<"INGRESOS TOTALES POR PUBLICIDAD: "<<"$ "<<right<<setw(10)<<ingresosTotal<<left<<endl;
    cout<<setw(50)<<"CANAL CON MAYORES INGRESOS POR PUBLICIDAD: "<<codeCharM<<codeNumM<<" CON $ "<<right<<setw(10)<<ingresoM<<endl;
}