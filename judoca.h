#ifndef __JUDOCA_H__
#define __JUDOCA_H__

#include <stddef.h>

typedef struct {
    char *nombre, *apellido;
    int edad;
} _Judoca;

typedef _Judoca* Judoca;

typedef struct {
    Judoca participante1, participante2;
    int estadoPareja;
} _Pareja ;

typedef _Pareja* Pareja;

typedef struct _TNodo {
    void *dato;
    struct _TNodo *izq, *der;
} TNodo;

typedef TNodo* Arbol;

#endif
