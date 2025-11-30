//
// Created by sn on 11/29/25.
//

#ifndef LAB09_2025_2_LISTASLIGADAS_FUNCIONES_H
#define LAB09_2025_2_LISTASLIGADAS_FUNCIONES_H

#include "Nodo.h"
#include "Categoria.h"

void leeDatosEImprimeReporte(const char* , const char* , const char* , const char* , const char* );
void leerCategorias(const char* , Nodo*& );
void openError(const char* );
char* leerCadenaExacta(ifstream& , char );
void insertarOrdenado(Nodo*& , Categoria ) ;
void emitirReporte(const char* ,  Nodo* );
void imprimirLinea(ofstream& , char );
void leerStreams(const char* fn, Nodo* );
Nodo* buscarNodo(Nodo* , const char* );
void calcularDropOffPromedio(Nodo* );
void eliminarCategorias(Nodo*& , double );

#endif //LAB09_2025_2_LISTASLIGADAS_FUNCIONES_H