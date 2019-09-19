#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "judoca.h"

typedef void (*Destruir) (void *dato);

typedef int (*Comparar) (void *dato1, void *dato2);

typedef void (*Mostrar) (void *dato);

/**************************************************************/

int comparar_judoca(void *dato1, void *dato2) {
    return (((Judoca)dato1) -> edad < ((Judoca)dato2) -> edad);
}

int comparar_pareja(void *dato1, void *dato2) {
    return (((Pareja)dato1) -> estadoPareja < ((Pareja)dato2) -> estadoPareja);
}

Arbol nuevo_nodo(Arbol arbol, void *dato, Comparar c) {
    if(!arbol) {
        arbol = malloc(sizeof(TNodo));
        arbol -> dato = dato;
        arbol -> izq = NULL;
        arbol -> der = NULL;
    } else {
        if(c(arbol -> dato, dato))
            arbol -> der = nuevo_nodo(arbol -> der, dato, c);
        else arbol -> izq = nuevo_nodo(arbol -> izq, dato, c);
    }
    return arbol;
}

Arbol mayor_de_menores(Arbol arbol){
	if(!(arbol -> izq)) {
    	return NULL;
  	} else {
	    Arbol nodo;
    	for(nodo = arbol -> izq; nodo -> der; nodo = nodo -> der);
    	return nodo;
  	}
}

void destruir_judoca(Judoca judoca) {
    free(judoca -> nombre);
    free(judoca -> apellido);
    free(judoca);
}

Arbol eliminar_nodo(Arbol arbol, void *dato, Comparar c, Destruir d) {
	if (!arbol) return NULL;
	if (arbol -> dato != dato) {
		if (c(arbol -> dato, dato))
			arbol -> der = eliminar_nodo(arbol -> der, dato, c, d);
    	else
    		arbol -> izq = eliminar_nodo(arbol -> izq, dato, c, d);
  	} else {
  		if (!(arbol -> izq) && !(arbol -> der))	{
            d(arbol -> dato);
  			free(arbol);
  			return NULL;
  		} else if (!(arbol -> izq) || !(arbol -> der)) {
  			Arbol nodo = !(arbol -> izq) ? arbol -> der : arbol -> izq;
            d(arbol -> dato);
  			free(arbol);
  			return nodo;
  		} else {
  			Arbol nodo = mayor_de_menores(arbol);
  			arbol -> dato = nodo -> dato;
  			arbol -> izq = eliminar_nodo(arbol -> izq, nodo -> dato, c, d);
  		}
  	}
  	return arbol;
}

Judoca crear_judoca(char nombre[], char apellido[], int edad) {
    Judoca nuevo_judoca = malloc(sizeof(_Judoca));
    nuevo_judoca -> nombre = malloc(sizeof(char) * strlen(nombre) + 1);
    nuevo_judoca -> apellido = malloc(sizeof(char) * strlen(apellido) + 1);

    strcpy(nuevo_judoca -> nombre, nombre);
    strcpy(nuevo_judoca -> apellido, apellido);
    nuevo_judoca -> edad = edad;
    nuevo_judoca -> emparejado = 0;

    return nuevo_judoca;
}

Arbol ingresar_equipo1(Arbol equipo1, FILE *entrada) {
    char basura[16], nombre[32], apellido[32];
    int edad, correcto;
    fscanf(entrada, "%s", basura);
    fgetc(entrada);
    for(correcto = 1; correcto;) {
        fscanf(entrada, "%[^,\n]", nombre);
        if(strcmp(nombre, "Equipo2:")) {
            fscanf(entrada, ",%[^,],%d", apellido, &edad);
            fgetc(entrada);

            Judoca nuevo_judoca = crear_judoca(nombre, apellido, edad);

            equipo1 = nuevo_nodo(equipo1, nuevo_judoca, comparar_judoca);
        } else correcto = 0;
    }
    fgetc(entrada);
    return equipo1;
}

Arbol ingresar_equipo2(Arbol equipo2, FILE *entrada) {
    char nombre[32], apellido[32];
    int edad, correcto;
    for(correcto = 1; correcto;) {
        if(fscanf(entrada, "%[^,],%[^,],%d", nombre, apellido, &edad) == 3) {
            fgetc(entrada);

            Judoca nuevo_judoca = crear_judoca(nombre, apellido, edad);

            equipo2 = nuevo_nodo(equipo2, nuevo_judoca, comparar_judoca);
        } else correcto = 0;
    }
    return equipo2;
}

void mostrar_judoca(void *dato) {
    printf("%s, ", ((Judoca)dato) -> nombre);
    printf("%s, ", ((Judoca)dato) -> apellido);
    printf("%d\n", ((Judoca)dato) -> edad);
}

void mostrar(Arbol equipo, Mostrar m) {
    if(equipo) {
        m(equipo -> dato);
        mostrar(equipo -> izq, m);
        mostrar(equipo -> der, m);
    }
}

int max_judoca(Judoca judoca1, Judoca judoca2) {
    if(judoca1 -> edad > judoca2 -> edad)
        return judoca1 -> edad;
    return judoca2 -> edad;
}

int min_judoca(Judoca judoca1, Judoca judoca2) {
  if(judoca1 -> edad < judoca2 -> edad)
      return judoca1 -> edad;
  return judoca2 -> edad;

}

int pareja_valida(Judoca judoca1, Judoca judoca2) {
    if((judoca1 -> edad < 18 && judoca2 -> edad >= 18) || (judoca1 -> edad >= 18 && judoca2 -> edad < 18))
        return 1;

    if(judoca1 -> edad < 18) {
        if(max_judoca(judoca1, judoca2) - min_judoca(judoca1, judoca2) > 1)
            return 2;
    }
    if(judoca1 -> edad >= 18) {
        if(max_judoca(judoca1, judoca2) - min_judoca(judoca1, judoca2) > 2)
            return 3;
    }
    return 0;
}

Pareja crear_pareja(Judoca participante1, Judoca participante2, int estadoPareja) {
    Pareja nueva_pareja = malloc(sizeof(_Pareja));
    nueva_pareja -> participante1 = participante1;
    nueva_pareja -> participante2 = participante2;
    nueva_pareja -> estadoPareja = estadoPareja;
    return nueva_pareja;
}

/*Arbol emparejar(Arbol equipo1, Arbol equipo2, Arbol parejas, Comparar c){
    if(!(equipo1 -> ((Judoca)dato) -> emparejado)) {
        if(!(equipo2 -> ((Judoca)dato) -> emparejado)) {
            if(!pareja_valida(equipo1 -> dato, equipo2 -> dato)){


            }
        }
    }
}*/

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Cantidad de argumentos invalida\n");
        return 0;
    }
    FILE *entrada;
    entrada = fopen(argv[1], "r");

    Arbol equipo1 = NULL;
    Arbol equipo2 = NULL;

    equipo1 = ingresar_equipo1(equipo1, entrada);
    equipo2 = ingresar_equipo2(equipo2, entrada);

    Arbol parejas = NULL;
    for(;equipo1 || equipo2;) {
        parejas = emparejar(equipo1, equipo2, parejas, comparar_pareja);
    }

    return 0;
}
