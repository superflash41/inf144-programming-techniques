//
// Created by sn on 11/4/25.
//

#ifndef LABORATORIO06_2025_2_CADENAS_FUNCIONES_H
#define LABORATORIO06_2025_2_CADENAS_FUNCIONES_H

void leeDatosEImprimeReporte(const char* , const char* , const char* );
void leerCategorias(const char* , char** , char** , int& );
void openError(const char* );
char* leerCadenaExacta(ifstream& , char );
char* reporteDePrueba(const char* , const char* );
void emitirReportePruebaCategorias(const char* , char** , char** , int );
void leerStreams(const char* , int* , char** , char** , double* , double* , int* , int& );
int convert(int , int , int , char );
void emitirReportePruebaStreams(const char* , int* , char** , char** , double* , double* , int* , int );
void imprimirReportes(const char* , char** , char** , int , int* , char** , char** , double* , double* ,
    int* , int );
void generaArchivoEnlace(const char* , char*& , char*& );
char* format(const char* );
void imprimirReporteCategoria(const char* , const char* , const char* , const char* , int* ,
    char** , char** , double* , double* , int* , int );
void imprimirCabecera(ofstream& , const char* , const char* , const char* );
void imprimeLinea(ofstream& , char );
void imprimirResumen(ofstream& , double , double , int );

#endif //LABORATORIO06_2025_2_CADENAS_FUNCIONES_H