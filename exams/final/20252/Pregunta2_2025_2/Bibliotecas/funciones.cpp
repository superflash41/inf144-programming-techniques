//
// Created by superflash41 on 1/12/2025.
//

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

#include "funciones.h"
#include "Nodo.h"
#include "Palabra.h"

// a todos le puse el mismo reporte porque me dio flojera
void resolverPreguntaDos(const char* fnStopWords, const char* fnComentarios,
    const char* fnRepSW, const char* fnC, const char* fnF, const char* fnRep) {
    Nodo* stopwords = nullptr, *palabras = nullptr, *frecuencias = nullptr; // no olvides inicializar
    leerStopWords(stopwords, fnStopWords);
    imprimirReporteLista(stopwords, fnRepSW);
    leerPalabras(palabras, fnComentarios);
    imprimirReporteLista(palabras, fnC);
    removerPalabrasDeStopWords(palabras, stopwords);
    imprimirReporteLista(palabras, fnF);
    crearListaFrecuencias(palabras, frecuencias);
    imprimirReporteLista(frecuencias, fnRep);
}

void leerStopWords(Nodo*& sll, const char* fn) {
    ifstream arch(fn, ios::in);
    if (!arch.is_open()) openError(fn);
    Palabra p{};
    p.cantidad++;
    while (true) {
        p.preproc = leerCadenaExacta(arch, '\n');
        if (!p.preproc) break;
        insertar(sll, p);
    }
}

void openError(const char* fn) {
    cout << "Error al abrir el archivo: " << fn << endl;
    exit(1);
}

char* leerCadenaExacta(ifstream& arch, char c) {
    char s[100];
    arch.getline(s, 100, c);
    if (arch.eof()) return nullptr;
    char* pt = new char[strlen(s) + 1]{};
    strcpy(pt, s);
    return pt;
}

void insertar(Nodo*& sll, Palabra p) {
    Nodo* pt = sll, *prev = nullptr, *nuevo = new Nodo();
    nuevo->palabra = p;
    for (; pt; pt = pt->siguiente) prev = pt;
    nuevo->siguiente = nullptr;
    if (!prev) sll = nuevo;
    else prev->siguiente = nuevo;
}

// que dolor de cabeza el formato de los palitos
void imprimirReporteLista(Nodo* p, const char* fn) {
    ofstream arch(fn, ios::out);
    if (!arch.is_open()) openError(fn);
    arch<<setw(34)<<"PALABRAS FRECUENTES"<<endl;
    arch<<setw(36)<<"TRANSMISIONES NOVIEMBRE"<<endl;
    imprimirLinea(arch, '=');
    arch<<setw(20)<<"|ORIGINAL"<<"|"<<setw(30)<<"PREPROCESADA"<<"|    "<<setw(30)<<"CANTIDAD|"<<endl;
    imprimirLinea(arch, '-');
    for (; p; p=p->siguiente) {
        if (p->palabra.original) arch<<left<<"|"<<setw(20)<<p->palabra.original<<"|";
        else arch<<setw(20)<<" ";
        arch<<left<<setw(30)<<p->palabra.preproc<<"|"<<right<<setw(12)<<p->palabra.cantidad<<"|"<<endl;
    }
    imprimirLinea(arch, '=');
}

void imprimirLinea(ofstream& arch, char c) {
    arch<<left<<setfill(c)<<setw(66)<<" "<<setfill(' ')<<endl;
}

void leerPalabras(Nodo*& sll, const char* fn) {
    ifstream arch(fn, ios::in);
    if (!arch.is_open()) openError(fn);
    char s[50];
    while (true) {
        arch.getline(s, 100, ','); // descartable
        if (arch.eof()) break;
        arch.getline(s, 100, ','); // descartable
        procesarPalabras(sll, arch);
    }
}

void procesarPalabras(Nodo*& sll, ifstream& arch) {
    Nodo* pos;
    char s[100];
    while (true) {
        arch>>s;
        if (arch.get()=='\n') break;
        if (!(pos=buscarPalabra(sll, s)))
            pos = insertarPalabra(sll, s);
        pos->palabra.cantidad++;
    }
}

Nodo* buscarPalabra(Nodo* p, char* palabra) {
    for (; p; p=p->siguiente)
        if (!strcmp(p->palabra.original, palabra)) return p;
    return nullptr;
}

Nodo* insertarPalabra(Nodo*& sll, char* palabra) {
    Nodo* p = sll, *prev = nullptr, *nuevo = new Nodo();
    nuevo->palabra.original = new char[strlen(palabra)+1]{};
    strcpy(nuevo->palabra.original, palabra);
    nuevo->palabra.preproc = preProcesar(palabra);
    nuevo->palabra.cantidad = 0;
    for (; p; p = p->siguiente) prev = p;
    nuevo->siguiente = nullptr;
    if (!prev) sll = nuevo;
    else prev->siguiente = nuevo;
    return nuevo;
}

char* preProcesar(char * palabra) {
    char s[100]{};
    for (int i=0, j=0; palabra[i]; i++)
        if (palabra[i]>='A' and palabra[i]<='Z' or palabra[i]>='a' and palabra[i]<='z')
            s[j++] = (palabra[i] += (palabra[i]>='A' and palabra[i]<='Z') ? 'a' - 'A' : 0);
    char* procesada = new char[strlen(s)+1]{};
    strcpy(procesada, s);
    return procesada;
}

void removerPalabrasDeStopWords(Nodo*& palabras, Nodo* stopwords) {
    Nodo* p = palabras, *prev = nullptr, *eliminar = nullptr;
    while (p)
        if (inStopWords(stopwords, p->palabra.preproc)) {
            eliminar = p;
            if (!prev) palabras = palabras->siguiente;
            else prev->siguiente = p->siguiente;
            p = p->siguiente;
            delete[] eliminar->palabra.original;
            delete[] eliminar->palabra.preproc;
            delete eliminar;
        } else {
            prev = p;
            p = p->siguiente;
        }
}

bool inStopWords(Nodo* p, char* s) {
    for (; p; p=p->siguiente)
        if (!strcmp(p->palabra.preproc, s)) return true;
    return false;
}

void crearListaFrecuencias(Nodo* p, Nodo*& sll) {
    for (; p; p=p->siguiente) insertarOrdenado(sll, p->palabra);
}

// lo mismo que insertar pero ordenado
void insertarOrdenado(Nodo*& sll, Palabra p) {
    Nodo* pt = sll, *prev = nullptr, *nuevo = new Nodo();
    nuevo->palabra = p;
    for (; pt and (pt->palabra.cantidad>p.cantidad or
        pt->palabra.cantidad==p.cantidad and
        strcmp(pt->palabra.preproc, p.preproc)>0); pt = pt->siguiente)
        prev = pt;
    nuevo->siguiente = pt;
    if (!prev) sll = nuevo;
    else prev->siguiente = nuevo;
}