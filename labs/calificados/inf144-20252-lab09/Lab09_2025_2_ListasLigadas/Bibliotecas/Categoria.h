//
// Created by sn on 11/29/25.
//

#ifndef LAB09_2025_2_LISTASLIGADAS_CATEGORIA_H
#define LAB09_2025_2_LISTASLIGADAS_CATEGORIA_H

struct Categoria {
    char* codigo;
    char* nombre;
    char* descripcion;
    char* canalConDuracionMaxima;
    int duracionMaxima;
    int duracionTotal;
    double arrDropOff[20];
    int cantidadDeReproducciones;
    double promedioDropOff;
};

#endif //LAB09_2025_2_LISTASLIGADAS_CATEGORIA_H