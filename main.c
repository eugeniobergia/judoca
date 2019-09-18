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
	if  (!(arbol -> izq)) {
    	return NULL;
  	} else {
	    Arbol nodo;
    	for(nodo = arbol -> izq; nodo -> der; nodo = nodo -> der);
    	return nodo;
  	}
}

Arbol eliminar_nodo(Arbol arbol, void *dato, Comparar c) {
	if (!arbol) return NULL;
	if (arbol -> dato != dato) {
		if (c(arbol -> dato, dato))
			arbol -> der = eliminar_nodo(arbol -> der, dato, c);
    	else
    		arbol -> izq = eliminar_nodo(arbol -> izq, dato, c);
  	} else {
  	//Estoy en el Nodo que se desea eliminar
  		//Caso 1: No tiene hijos
  		if (!(arbol -> izq) && !(arbol -> der))	{
  			free(arbol);
  			return NULL;
  		}
  		//Caso 2: Un hijo
  		else if (!(arbol -> izq) || !(arbol -> der)) {
  			Arbol nodo = !(arbol -> izq) ? arbol -> der : arbol -> izq;
  			free(arbol);
  			return nodo;
  		}
  		//Caso 3: 2 hijos
  		else {
  			//Encuentro el nodo que tengo que poner en su lugar, en este caso, es el mayor de los menores
  			Arbol nodo = mayor_de_menores(arbol);
  			arbol -> dato = nodo -> dato;
  			//Borro el nodo duplicado que quedó
  			arbol -> izq = eliminar_nodo(arbol -> izq, nodo -> dato, c);
  		}
  	}
  	return arbol;
}

Arbol ingresar_equipo(Arbol equipo, FILE *entrada) {
    char basura[16], nombre[32], apellido[32];
    int edad, correcto = 1;
    fscanf(entrada, "%s", basura);
    fgetc(entrada);
    for(;correcto;) {
        if(fscanf(entrada, "%[^,],%[^,],%d", nombre, apellido, &edad) == 3) {
            fgetc(entrada);
            Judoca nuevo_judoca = malloc(sizeof(_Judoca));
            nuevo_judoca -> nombre = malloc(sizeof(char) * strlen(nombre) + 1);
            nuevo_judoca -> apellido = malloc(sizeof(char) * strlen(apellido) + 1);

            strcpy(nuevo_judoca -> nombre, nombre);
            strcpy(nuevo_judoca -> apellido, apellido);
            nuevo_judoca -> edad = edad;

            equipo = nuevo_nodo(equipo, nuevo_judoca, comparar_judoca);
        } else correcto = 0;
    }
    return equipo;
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
        if(max_judoca(judoca1, judoca2) - max_judoca(judoca1, judoca2) > 1)
            return 2;
    }
    if(judoca1 -> edad >= 18) {
        if(max_judoca(judoca1, judoca2) - max_judoca(judoca1, judoca2) > 2)
            return 3;
    }
    return 0;
}



int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Cantidad de argumentos invalida\n");
        return 0;
    }
    FILE *entrada1, *entrada2, *salida;
    entrada1 = fopen(argv[1], "r");
    entrada2 = fopen(argv[2], "r");
    salida = fopen(argv[3], "w");

    Arbol equipo1 = NULL;
    Arbol equipo2 = NULL;

    equipo1 = ingresar_equipo(equipo1, entrada1);
    equipo2 = ingresar_equipo(equipo2, entrada2);

    mostrar(equipo1, mostrar_judoca);
    printf("\n");
    mostrar(equipo2, mostrar_judoca);

    Arbol parejas;
    for(;equipo1;)
        parejas = emparejar(&equipo1, &equipo2);

    return 0;
}
