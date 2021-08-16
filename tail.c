#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cola.h"

char* leer_linea(){

	char* linea = NULL;
	size_t cant = 0;
	ssize_t lineas;

	if((lineas = getline(&linea, &cant, stdin)) > 0){
		return linea;
	}

	free(linea);

	return NULL;
}

void tail(int cant_lineas){

	char* linea = NULL, *linea_anterior;
	size_t contador_lineas = 0;
	cola_t* cola_lineas = cola_crear();

	if(!cola_lineas) return;

	while((linea = leer_linea()) != NULL){
		if(contador_lineas == cant_lineas){
			linea_anterior = cola_desencolar(cola_lineas);
			free(linea_anterior);
		}else{
			contador_lineas++;
		}
		cola_encolar(cola_lineas, linea);
	}

	while(!cola_esta_vacia(cola_lineas)){
		char* linea_actual = cola_desencolar(cola_lineas);
		fprintf(stdout, "%s", linea_actual);
		free(linea_actual);
	}
	
	cola_destruir(cola_lineas, NULL);
}

int main(int argc, char* argv[]){

	if(argc != 2){
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	}

	int cant_lineas = atoi(argv[1]);

	if(cant_lineas <= 0){
		fprintf(stderr, "%s\n", "Tipo de parametro incorrecto");
		return 1;
	}

	tail(cant_lineas);

	return 0;
}
