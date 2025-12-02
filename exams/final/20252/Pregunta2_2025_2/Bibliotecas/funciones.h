//
// Created by superflash41 on 1/12/2025.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Nodo.h"
#include "Palabra.h"

void resolverPreguntaDos(const char* , const char* ,
    const char* , const char* , const char* , const char* );
void leerStopWords(Nodo*& , const char* );
void openError(const char* );
char* leerCadenaExacta(ifstream& , char );
void insertar(Nodo*& , Palabra );
void imprimirReporteLista(Nodo* , const char* );
void imprimirLinea(ofstream& , char );
void leerPalabras(Nodo*& , const char* );
void procesarPalabras(Nodo*& , ifstream& );
Nodo* buscarPalabra(Nodo*p, char* );
Nodo* insertarPalabra(Nodo*& , char* );
char* preProcesar(char * );
void removerPalabrasDeStopWords(Nodo*& , Nodo* );
bool inStopWords(Nodo*p, char*s);
void crearListaFrecuencias(Nodo* , Nodo*& );
void insertarOrdenado(Nodo*& , Palabra );

#endif //FUNCIONES_H
