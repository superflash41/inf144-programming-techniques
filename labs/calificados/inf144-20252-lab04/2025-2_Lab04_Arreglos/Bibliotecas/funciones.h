//
// Created by sn on 10/2/25.
//

#ifndef INC_2025_2_LAB04_ARREGLOS_FUNCIONES_H
#define INC_2025_2_LAB04_ARREGLOS_FUNCIONES_H

void leeDatosEImprimeReporte(const char* , const char* , const char* , const char* );
void leerCanales(const char* , int* , int* , char* , double* , int& );
void openError(const char* );
void leerEtiquetas(const char* , int* , int* , int& );
void imprimirReportePreliminar(int* , int* , char* , double* , int , int* , int* , int );
void imprimirCanalesPrelim(ofstream& , int* , int* , char* , double* , int );
void imprimeLinea(ofstream& , char );
void imprimirEtiquetasPrelim(ofstream& , int* , int* , int );
void actualizarArreglos(const char* , int* , char* , int* , int* , int* , int* , double* , int* ,
    int* , int* , double* , int , int , double );
int buscarCanal(int , char , int* , char* , int );
void actualizarCanal(int , int* , int* , int , int , int& , int& );
int buscarEtiqueta(int , int* , int );
void actualizarEtiqueta(int , char , int* , char* , int , int , int& , int& , int );
void actualizarIngresos(int* , double* , int* , double* , int , double );
void imprimirReporteFinal(const char* , int* , int* , char* , double* ,
    int* , int* , int* , double* , int , int* , int* ,
    int* , int* , int , double );
void imprimirCanalesFinal(ofstream& , int* , int* , char* , double* , int* , int* , int* , double* , int );
void imprimirEtiquetasFinal(ofstream& , int* , int* , int* , int* , int );

#endif //INC_2025_2_LAB04_ARREGLOS_FUNCIONES_H