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

/**************************************************************/

typedef void (*Destruir) (void *dato);

typedef int (*Comparar) (void *dato1, void *dato2);

typedef void (*Mostrar) (void *dato);

typedef void (*Imprimir) (void *dato, FILE *archivo);

/**************************************************************/

int comparar_judoca(void *dato1, void *dato2);

int comparar_pareja(void *dato1, void *dato2);

Arbol nuevo_nodo(Arbol arbol, void *dato, Comparar c);

Arbol mayor_de_menores(Arbol arbol);

Arbol eliminar_nodo(Arbol arbol, void *dato, Comparar c);

Judoca crear_judoca(char nombre[], char apellido[], int edad);

Arbol ingresar_equipo1(Arbol equipo1, FILE *entrada);

Arbol ingresar_equipo2(Arbol equipo2, FILE *entrada);

void mostrar_judoca(void *dato);

void mostrar_pareja(void *dato);

void mostrar(Arbol equipo, Mostrar m);

int max_judoca(Judoca judoca1, Judoca judoca2);

int min_judoca(Judoca judoca1, Judoca judoca2);

int pareja_valida(Judoca judoca1, Judoca judoca2);

Pareja crear_pareja(Judoca participante1, Judoca participante2, int estadoPareja);

Arbol emparejar(Arbol *equipo1, Arbol *equipo2, Arbol parejas);

void imprimir_judoca(void *dato, FILE *salida);

void imprimir_pareja(void *dato, FILE *salida);

void imprimir_salida(Arbol arbol, FILE *salida, Imprimir i);

void destruir_judoca(void *judoca);

void destruir_pareja(void *pareja);

Arbol destruir_arbol(Arbol arbol, Destruir d);

#endif
