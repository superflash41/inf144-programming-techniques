#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "funciones.h"
#include "Nodo.h"
#include "Categoria.h"

#define DROPOFF_THRESHOLD 3.5

void leeDatosEImprimeReporte(const char* fnCategorias, const char* fnStreams, const char* fnRepPrueba,
    const char* fnRepCompleto, const char* fnRepEliminiado) {
    Nodo* sll;
    leerCategorias(fnCategorias, sll);
    emitirReporte(fnRepPrueba, sll);
    leerStreams(fnStreams, sll);
    calcularDropOffPromedio(sll);
    emitirReporte(fnRepCompleto, sll);
    eliminarCategorias(sll, DROPOFF_THRESHOLD);
    emitirReporte(fnRepEliminiado, sll);
}

void leerCategorias(const char* fn, Nodo*& sll) {
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    sll = nullptr; // inicializacion de la lista
    Categoria c{}; // inicializamos cada categoria (campos en 0 para todas)
    while (true) {
        c.codigo = leerCadenaExacta(arch, ',');
        if (!c.codigo) break;
        c.nombre = leerCadenaExacta(arch, ',');
        c.descripcion = leerCadenaExacta(arch, '\n');
        insertarOrdenado(sll, c);
    }
}

void openError(const char* fn) {
    cout<<"Error al abrir el archivo: "<<fn<<endl;
    exit(1);
}

char* leerCadenaExacta(ifstream& arch, char c) {
    char s[150];
    arch.getline(s, 150, c);
    if (arch.eof()) return nullptr;
    char* pt = new char[strlen(s)+1]{};
    strcpy(pt, s);
    return pt;
}

void insertarOrdenado(Nodo*& sll, Categoria c) {
    Nodo* p = sll, *prev = nullptr, *toInsert = new Nodo;
    toInsert->categoria = c;
    for (; p and strcmp(p->categoria.codigo, c.codigo)<0; p=p->siguiente)
        prev = p;
    toInsert->siguiente = p;
    if (!prev) sll = toInsert;
    else prev->siguiente = toInsert;
}

void emitirReporte(const char* fn,  Nodo* p) {
    ofstream arch(fn, ios::out);
    if (not arch.is_open()) openError(fn);
    arch<<setprecision(2)<<fixed;
    arch<<setw(30)<<"REPORTE DE PRUEBA DE CATEGORIAS"<<endl;
    for (; p; p=p->siguiente) {
        imprimirLinea(arch, '=');
        arch<<left<<setw(30)<<"Codigo:"<<p->categoria.codigo<<endl;
        arch<<setw(30)<<"Nombre:"<<p->categoria.nombre<<endl;
        arch<<setw(30)<<"Descripcion:"<<p->categoria.descripcion<<endl;
        if (!p->categoria.cantidadDeReproducciones) continue;
        imprimirLinea(arch, '-');
        arch<<"INFORMACION DE LAS REPRODUCCIONES:"<<endl;
        arch<<"DURACION MAXIMA:"<<endl;
        arch<<setw(30)<<"NOMBRE DEL CANAL:"<<p->categoria.canalConDuracionMaxima<<endl;
        arch<<setw(30)<<"DURACION:"<<setfill('0')<<right<<
            setw(2)<<p->categoria.duracionMaxima/3600<<":"<<
            setw(2)<<(p->categoria.duracionMaxima%3600)/60<<":"<<
            setw(2)<<p->categoria.duracionMaxima%60<<setfill(' ')<<left<<endl;
        imprimirLinea(arch, '-');
        arch<<setw(30)<<"LISTA DE DROP OFF: ";
        for (int i=0; i<p->categoria.cantidadDeReproducciones; i++)
            arch<<setw(6)<<p->categoria.arrDropOff[i];
        arch<<endl;
        arch<<setw(30)<<"PROMEDIO DE DROP-OFF:"<<p->categoria.promedioDropOff<<endl;
        arch<<setw(30)<<"TIEMPO DE DURACION TOTAL:"<<setfill('0')<<right<<
            setw(2)<<p->categoria.duracionTotal/3600<<":"<<
            setw(2)<<(p->categoria.duracionTotal%3600)/60<<":"<<
            setw(2)<<p->categoria.duracionTotal%60<<setfill(' ')<<left<<endl;
    }
}

void imprimirLinea(ofstream& arch, char c) {
    arch<<setfill(c)<<setw(90)<<c<<setfill(' ')<<endl;
}

void leerStreams(const char* fn, Nodo* sll) {
    ifstream arch(fn, ios::in);
    if (not arch.is_open()) openError(fn);
    int hh, mm, ss;
    char s[50], c;
    double dropoff;
    Nodo* p;
    while (true) {
        arch.getline(s, 50, ',');
        if (arch.eof()) break;
        if (p=buscarNodo(sll, s)) {
            arch.getline(s, 50, ',');
            arch>>dropoff>>c>>hh>>c>>mm>>c>>ss;
            p->categoria.duracionTotal += hh*3600+mm*60+ss;
            p->categoria.arrDropOff[p->categoria.cantidadDeReproducciones] = dropoff;
            p->categoria.cantidadDeReproducciones++;
            if (p->categoria.duracionMaxima < (hh*3600+mm*60+ss)) {
                p->categoria.duracionMaxima = hh*3600+mm*60+ss;
                p->categoria.canalConDuracionMaxima = new char[strlen(s)+1]{};
                strcpy(p->categoria.canalConDuracionMaxima, s);
            }
        }
        while (arch.get()!='\n');
    }
}

Nodo* buscarNodo(Nodo* p, const char* codigo) {
    for (; p; p=p->siguiente)
        if (!strcmp(p->categoria.codigo, codigo)) return p;
    return nullptr;
}

void calcularDropOffPromedio(Nodo* p) {
    for (; p; p=p->siguiente) {
        for (int i=0; i<p->categoria.cantidadDeReproducciones; i++)
            p->categoria.promedioDropOff += p->categoria.arrDropOff[i];
        if (p->categoria.cantidadDeReproducciones)
            p->categoria.promedioDropOff /= p->categoria.cantidadDeReproducciones;
    }
}

// no hice delete, pero si quieres puedes hacerlo con un array de direcciones
void eliminarCategorias(Nodo*& sll, double threshold) {
    if (!sll) return;
    Nodo* p = sll, *prev = nullptr;
    for (; p; p=p->siguiente)
        if (p->categoria.promedioDropOff < threshold) {
            if (!prev) sll = p->siguiente;
            else prev->siguiente=p->siguiente;
        } else prev = p;
}