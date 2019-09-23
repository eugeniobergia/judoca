#ifndef __JUDOCA_H__
#define __JUDOCA_H__

#include <stddef.h>

/*****ESTRUCTURAS*****/

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

/*****PUNTEROS A FUNCION*****/

typedef void (*Destruir) (void *dato);

typedef int (*Comparar) (void *dato1, void *dato2);

typedef void (*Mostrar) (void *dato);

typedef void (*Imprimir) (void *dato, FILE *archivo);

/*****FUNCIONES*****/

/*
 * Compara dos judocas mediante sus edades
 * Retorna -1 si el primero es menor al segundo
 * Retorna 1 si el primero es mayor al segundo
 * Retorna 0 si son iguales
 */
int comparar_judoca(void *dato1, void *dato2);

/*
 * Compara dos parejas mediante sus estados
 * Retorna -1 si el primero es menor al segundo
 * Retorna 1 si el primero es mayor al segundo
 * Retorna 0 si son iguales
 */
int comparar_pareja(void *dato1, void *dato2);

/*
 * Crea un nuevo nodo en un arbol dado
 */
Arbol nuevo_nodo(Arbol arbol, void *dato, Comparar c);

/*
 * Retorna el mayor nodo de los menores a un nodo dado
 */
Arbol mayor_de_menores(Arbol arbol);


/*
 * Elimina un nodo de un arbol dado, pero no lo libera
 */
Arbol eliminar_nodo(Arbol arbol, void *dato, Comparar c);


/*
 * Reserva memoria para un nuevo judoca con los datos dados, y lo retorna
 */
Judoca crear_judoca(char nombre[], char apellido[], int edad);

/*
 * Retorna un arbol para el equipo 1, leyendo un archivo de entrada
 */
Arbol ingresar_equipo1(Arbol equipo1, FILE *entrada);

/*
 * Retorna un arbol para el equipo 2, leyendo un archivo de entrada
 */
Arbol ingresar_equipo2(Arbol equipo2, FILE *entrada);


/*
 * Muestra un judoca en pantalla
 */
void mostrar_judoca(void *dato);

/*
 * Muestra una pareja en pantalla
 */
void mostrar_pareja(void *dato);

/*
 * Muestra todo un arbol en pantalla
 */
void mostrar(Arbol equipo, Mostrar m);

/*
 * Retorna la edad del mayor judoca
 */
int max_judoca(Judoca judoca1, Judoca judoca2);

/*
 * Retorna la edad del menor judoca
 */
int min_judoca(Judoca judoca1, Judoca judoca2);

/*
 * Determina si una pareja es valida
 * Retorna 0 si es valida
 * Retorna 1 si es una pareja de menor con un mayor
 * Retorna 2 si hay una diferencia mayor a 1 entre dos menores
 * Retorna 3 si hay una diferencia mayor a 2 entre dos mayores
 */
int pareja_valida(Judoca judoca1, Judoca judoca2);

/*
 * Toma dos judocas y su estado, y los empareja
 */
Pareja crear_pareja(Judoca participante1, Judoca participante2, int estadoPareja);

/*
 * Toma dos arboles de judocas, empareja sus raices, las elimina de su arboles
 * y retorna un arbol de parejas
 */
Arbol emparejar(Arbol *equipo1, Arbol *equipo2, Arbol parejas);

/*
 * Escribe un judoca en un archivo de salida
 */
void imprimir_judoca(void *dato, FILE *salida);

/*
 * Escribe una pareja en un archivo de salida
 */
void imprimir_pareja(void *dato, FILE *salida);

/*
 * Escribe todo un arbol en un archivo de salida
 */
void imprimir_salida(Arbol arbol, FILE *salida, Imprimir i);

/*
 * Libera la memoria de un judoca
 */
void destruir_judoca(void *judoca);

/*
 * Libera la memoria de una pareja
 */
void destruir_pareja(void *pareja);

/*
 * Libera la memoria de todo un arbol
 */
Arbol destruir_arbol(Arbol arbol, Destruir d);

#endif

// (^._.^) miau
