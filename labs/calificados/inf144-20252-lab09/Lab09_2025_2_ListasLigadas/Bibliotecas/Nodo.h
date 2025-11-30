//
// Created by sn on 11/29/25.
//

#ifndef LAB09_2025_2_LISTASLIGADAS_NODO_H
#define LAB09_2025_2_LISTASLIGADAS_NODO_H

#include "Categoria.h"

struct Nodo {
    Categoria categoria;
    Nodo* siguiente;
};

#endif //LAB09_2025_2_LISTASLIGADAS_NODO_H