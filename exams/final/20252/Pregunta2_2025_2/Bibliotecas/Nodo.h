//
// Created by superflash41 on 1/12/2025.
//

#ifndef NODO_H
#define NODO_H

#include "Palabra.h"

struct Nodo {
    Palabra palabra;
    struct Nodo *siguiente;
};

#endif //NODO_H
