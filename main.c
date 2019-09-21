#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "judoca.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Cantidad de argumentos invalida\n");
        return 0;
    }
    FILE *entrada, *salida;
    entrada = fopen(argv[1], "r");
    salida = fopen(argv[2], "w");

    Arbol equipo1 = NULL;
    Arbol equipo2 = NULL;

    equipo1 = ingresar_equipo1(equipo1, entrada);
    equipo2 = ingresar_equipo2(equipo2, entrada);

    Arbol parejas = NULL;
    for(; equipo1 && equipo2;)
        parejas = emparejar(&equipo1, &equipo2, parejas);

    fprintf(salida, "Las parejas formadas son las siguientes:\n");
    imprimir_salida(parejas, salida, imprimir_pareja);

    if(equipo1) {
        fprintf(salida, "\nLos siguientes judocas del equipo 1 quedaron sin emparejar:\n");
        imprimir_salida(equipo1, salida, imprimir_judoca);
    }
    if(equipo2) {
        fprintf(salida, "\nLos siguientes judocas del equipo 2 quedaron sin emparejar:\n");
        imprimir_salida(equipo2, salida, imprimir_judoca);
    }

    destruir_arbol(equipo1, destruir_judoca);
    destruir_arbol(equipo2, destruir_judoca);
    destruir_arbol(parejas, destruir_pareja);

    return 0;
}
