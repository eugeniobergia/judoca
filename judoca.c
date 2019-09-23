#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "judoca.h"

int comparar_judoca(void *dato1, void *dato2) {
    if(((Judoca)dato1) -> edad < ((Judoca)dato2) -> edad)
        return -1;
    if(((Judoca)dato1) -> edad > ((Judoca)dato2) -> edad)
        return 1;
    return 0;
}

int comparar_pareja(void *dato1, void *dato2) {
    if(((Pareja)dato1) -> estadoPareja < ((Pareja)dato2) -> estadoPareja)
        return -1;
    if(((Pareja)dato1) -> estadoPareja > ((Pareja)dato2) -> estadoPareja)
        return 1;
    return 0;
}

Arbol nuevo_nodo(Arbol arbol, void *dato, Comparar c) {
    if(!arbol) {
        arbol = malloc(sizeof(TNodo));
        arbol -> dato = dato;
        arbol -> izq = NULL;
        arbol -> der = NULL;
    } else {
        if(c(arbol -> dato, dato) < 0) // Comparo los datos y me fijo si el pimero es menor al segundo
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

Arbol eliminar_nodo(Arbol arbol, void *dato, Comparar c) {
	if (!arbol) return NULL;
	if (c(arbol -> dato, dato) != 0) { // Comparo los datos y me fijo si son diferentes
      if (c(arbol -> dato, dato) < 0) // Comparo los datos y me fijo si el pimero es menor al segundo
          arbol -> der = eliminar_nodo(arbol -> der, dato, c);
    	else
          arbol -> izq = eliminar_nodo(arbol -> izq, dato, c);
      } else {
          if (!(arbol -> izq) && !(arbol -> der))	{
              free(arbol);
              return NULL;
      		} else if (!(arbol -> izq) || !(arbol -> der)) {
              Arbol nodo = !(arbol -> izq) ? arbol -> der : arbol -> izq;
              free(arbol);
              return nodo;
      		} else {
              Arbol nodo = mayor_de_menores(arbol);
              arbol -> dato = nodo -> dato;
              arbol -> izq = eliminar_nodo(arbol -> izq, nodo -> dato, c);
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

    return nuevo_judoca;
}

Arbol ingresar_equipo1(Arbol equipo1, FILE *entrada) {
    char basura[16], nombre[32], apellido[32];
    int edad, correcto;
    fscanf(entrada, "%s", basura); // Lee la palabra "Equipo1"
    fgetc(entrada);
    for(correcto = 1; correcto;) {
        fscanf(entrada, "%[^,\n]", nombre); // Lee hasta que encuentra una coma o un salto de linea
        if(strcmp(nombre, "Equipo2:")) { // Si lee la palabra "Equipo2:" es porque ya termino de leer el equipo 1
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
        if(fscanf(entrada, "%[^,],%[^,],%d", nombre, apellido, &edad) == 3) { // Continua mientras lea correctamente 3 variables
            fgetc(entrada);

            Judoca nuevo_judoca = crear_judoca(nombre, apellido, edad);

            equipo2 = nuevo_nodo(equipo2, nuevo_judoca, comparar_judoca);
        } else correcto = 0;
    }
    return equipo2;
}

void mostrar_judoca(void *dato) {
    printf("%s,", ((Judoca)dato) -> nombre);
    printf("%s,", ((Judoca)dato) -> apellido);
    printf("%d", ((Judoca)dato) -> edad);
}

void mostrar_pareja(void *dato) {
    mostrar_judoca(((Pareja)dato) -> participante1);
    printf(" - ");
    mostrar_judoca(((Pareja)dato) -> participante2);
}

void mostrar(Arbol equipo, Mostrar m) {
    if(equipo) {
        m(equipo -> dato); // Muestro el dato
        printf("\n");
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

Arbol emparejar(Arbol *equipo1, Arbol *equipo2, Arbol parejas) {
    int estado_pareja = pareja_valida((*equipo1) -> dato, (*equipo2) -> dato);
    Pareja nueva_pareja = crear_pareja((*equipo1) -> dato, (*equipo2) -> dato, estado_pareja);
    parejas = nuevo_nodo(parejas, nueva_pareja, comparar_pareja);
    (*equipo1) = eliminar_nodo((*equipo1), (*equipo1) -> dato, comparar_judoca);
    (*equipo2) = eliminar_nodo((*equipo2), (*equipo2) -> dato, comparar_judoca);
    return parejas;
}

void imprimir_judoca(void *dato, FILE *salida) {
    fprintf(salida, "%s,%s,%d", ((Judoca)dato) -> nombre,((Judoca)dato) -> apellido, ((Judoca)dato) -> edad);
}

void imprimir_pareja(void *dato, FILE *salida) {
    imprimir_judoca(((Pareja)dato) -> participante1, salida);
    fprintf(salida, " - ");
    imprimir_judoca(((Pareja)dato) -> participante2, salida);
    fprintf(salida, " - ");
    if(((Pareja)dato) -> estadoPareja == 0)
        fprintf(salida, "Pareja valida");
    else if(((Pareja)dato) -> estadoPareja == 1)
        fprintf(salida, "Pareja de mayor con menor");
    else if(((Pareja)dato) -> estadoPareja == 2)
        fprintf(salida, "Pareja de menores con diferencia mayor a 1 año");
    else fprintf(salida, "Pareja de mayores con diferencia mayor a 2 años");
}

void imprimir_salida(Arbol arbol, FILE *salida, Imprimir i) {
    if(arbol) {
        imprimir_salida(arbol -> izq, salida, i);
        i(arbol -> dato, salida); // Escribo el dato en el archivo de salida
        fprintf(salida, "\n");
        imprimir_salida(arbol -> der, salida, i);
    }
}

void destruir_judoca(void *judoca) {
    free(((Judoca)judoca) -> nombre);
    free(((Judoca)judoca) -> apellido);
    free(((Judoca)judoca));
}

void destruir_pareja(void *pareja) {
    destruir_judoca(((Pareja)pareja) -> participante1);
    destruir_judoca(((Pareja)pareja) -> participante2);
    free(((Pareja)pareja));
}

Arbol destruir_arbol(Arbol arbol, Destruir d) {
    if(arbol) {
        arbol -> izq = destruir_arbol(arbol -> izq, d);
        arbol -> der = destruir_arbol(arbol -> der, d);
        d(arbol -> dato); // Libero el dato
        free(arbol);
    }
    return NULL; // Retorno NULL para que no quede apuntando a basura
}
