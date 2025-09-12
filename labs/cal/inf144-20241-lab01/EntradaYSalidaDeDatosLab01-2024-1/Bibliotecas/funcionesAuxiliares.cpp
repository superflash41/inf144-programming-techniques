//
// Created by sn on 9/2/25.
//

#include <iostream>
#include <iomanip>
using namespace std;
#include "funcionesAuxiliares.h"

// estructura de los datos que seran leidos
// dia/mes/anho   dni   hI:mI:sI  hF:mF:sF   tarifa  especialidad  hayReceta  montoMed

// funcion que lee e imprime al mismo tiempo informacion relacionada con las citas medicas
// al final se imprime un resumen
void leeDatosEImprimeReporte(void) {

    // variables para leer los datos
    int dia, mes, anho, dni, hI, mI, sI, hF, mF, sF;
    double tarifa, montoMed;
    char especialidad, c; // c es el caracter desechable

    // variables adicionales para guardar informacion relevante
    double total = 0.0; // total de ingresos
    double totalGastosMed = 0.0, dermaGastosMed = 0.0;
    // del reporte se puede ver que estos contadores van a ser necesarios
    int cantPac = 0, cantPacMed = 0, cantPacDerma = 0, cantPacPed = 0, cantPacCardFecha = 0, cantPacNoMedGasto = 0;

    imprimirEncabezadoReporte();
    while (true) {
        cin>>dia;
        if (cin.eof()) break; // no hay nada mas que leer
        cin>>c>>mes>>c>>anho>>dni>>hI>>c>>mI>>c>>sI>>hF>>c>>mF>>c>>sF>>tarifa>>especialidad;
        cin>>c; // lee 'S' o 'N'
        if (c == 'S') cin>>montoMed; // si hay monto por la medicina
        else montoMed = 0.0; // no hay medicina
        cout<<right<<setfill('0')<<setw(2)<<dia<<"/"<<setw(2)<<mes<<"/"<<setw(4)<<anho<<setfill(' ')<<setw(12)<<dni<<
            setw(4)<<" "<<setfill('0')<<setw(2)<<hI<<":"<<setw(2)<<mI<<":"<<setw(2)<<sI<<setfill(' ')<<
            setw(4)<<" "<<setfill('0')<<setw(2)<<hF<<":"<<setw(2)<<mF<<":"<<setw(2)<<sF<<setfill(' '); // imprimo hasta la hora de fin
        imprimeDatosYActualizaContadores(anho*10000+mes*100+dia, (hF*3600+mF*60+sF) - (hI*3600+mI*60+sI),
            tarifa, especialidad, c == 'S', montoMed, total, totalGastosMed, dermaGastosMed,
            cantPac, cantPacMed, cantPacDerma, cantPacPed, cantPacCardFecha, cantPacNoMedGasto);
    }
    imprimeResumenFinal(total, totalGastosMed/cantPacMed, dermaGastosMed/cantPacDerma,
        (cantPac-cantPacMed)*100.0/cantPac, cantPacPed*100.0/cantPac, cantPacCardFecha,
        cantPacNoMedGasto*100.0/cantPac);
}

// funcion para imprimir el encabezado del reporte y los titulos de las columnas
void imprimirEncabezadoReporte(void) {
    cout<<setw(70)<<"EMPRESA DE SALUD S.A."<<endl;
    imprimeLinea('=');
    cout<<setw(4)<<" "<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"<<endl;
    imprimeLinea('=');
    cout<<left<<setw(14)<<"Fecha"<<setw(12)<<"Paciente"<<setw(14)<<"Inicio"<<setw(8)<<"Fin"<<
        setw(16)<<"Duracion(H:M:S)"<<setw(12)<<"Duracion(H)"<<setw(14)<<"Especialidad"<<
            setw(20)<<"Pago(cita+medicamentos)"<<endl;
    imprimeLinea('-');
}

// funcion que imprime una linea para el reporte dado un caracter
void imprimeLinea(char c) {
    cout<<setfill(c)<<setw(120)<<" "<<setfill(' ')<<endl;
}

// esta funcion debe imprimir la duracion, especialidad, pago y actualizar los contadores para el reporte
void imprimeDatosYActualizaContadores(int fecha, int duracion, double tarifa, char especialidad, bool hayMed,
    double montoMed, double &total, double &totalGastosMed, double &dermaGastosMed, int &cantPac, int &cantPacMed,
            int &cantPacDerma, int &cantPacPed, int &cantPacCardFecha, int &cantPacNoMedGasto) {
    int hh, mm, ss; // son para la duracion
    double hFrac; // para guardar las horas en decimal
    double pago; // monto a pagar al medico (tarifa*hh + montoMed)
    hFrac = duracion/3600.0;
    hh = duracion/3600; // esto es para imprimir la hora de duracion
    mm = (duracion%3600)/60;
    ss = (duracion%3600)%60;
    pago = tarifa*hFrac + montoMed;
    cout<<setw(4)<<" "<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<mm<<":"<<setw(2)<<ss<<setfill(' ')<<
        setw(12)<<right<<hFrac<< setw(6)<<" "<<left;
    if (especialidad == 'C') cout<<setw(20)<<"Cardiologia";
    else if (especialidad == 'D') cout<<setw(20)<<"Dermatologia";
    else cout<<setw(20)<<"Pediatria";
    cout<<right<<setw(12)<<pago<<endl;
    // actualizamos los contadores
    cantPac++;
    total += pago;
    if (hayMed) {
        totalGastosMed += montoMed;
        cantPacMed++;
    } else if (pago >= 350.0) cantPacNoMedGasto++;
    if (especialidad == 'D') {
        dermaGastosMed += montoMed;
        cantPacDerma++;
    } else if (especialidad == 'P') cantPacPed++;
    else if (fecha > 20240115) cantPacCardFecha++;
}

void imprimeResumenFinal(double total, double promMed, double promMedDerma, double porcNoMed, double porcPed,
    int cantPacCardFecha, double porcPacNoMedGasto) {
    imprimeLinea('=');
    cout<<"Total de ingresos: "<<total<<endl;
    imprimeLinea('=');
    cout<<setw(4)<<" "<<"ESTADISTICAS OBTENIDAS:"<<endl;
    cout<<left<<setw(4)<<" "<<setw(100)<<"Promedio de gastos por medicina de los pacientes que le recetaron medicinas"<<
        right<<setw(10)<<promMed<<endl;
    cout<<left<<setw(4)<<" "<<setw(100)<<"Promedio de gastos por medicina de los pacientes que se atendieron en dermatologia"<<
        right<<setw(10)<<promMedDerma<<endl;
    cout<<left<<setw(4)<<" "<<setw(100)<<"Porcentaje de pacientes que no le recetaron medicinas"<<
        right<<setw(10)<<porcNoMed<<"%"<<endl;
    cout<<left<<setw(4)<<" "<<setw(100)<<"Porcentaje de pacientes que se atendieron en pediatria"<<
        right<<setw(10)<<porcPed<<"%"<<endl;
    cout<<left<<setw(4)<<" "<<setw(100)<<"Cantidad de pacientes que se atendieron en cardiologia despues del 15/01/2024"<<
        right<<setw(10)<<cantPacCardFecha<<endl;
    cout<<left<<setw(4)<<" "<<setw(100)<<"Porcentaje de pacientes que no le recetaron medicinas y que gasto mas de 350.00"<<
        right<<setw(10)<<porcPacNoMedGasto<<"%"<<endl;
}