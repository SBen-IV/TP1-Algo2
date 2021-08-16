#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void diff(FILE* archivo1, FILE* archivo2){

	char* linea1 = NULL, *linea2 = NULL;
	size_t cant1 = 0, cant2 = 0, num_linea = 1;
	ssize_t leidos1, leidos2;

	while((leidos1 = getline(&linea1, &cant1, archivo1) > 0) && (leidos2 = getline(&linea2, &cant2, archivo2) > 0)){
		if(strcmp(linea1, linea2) != 0){
			fprintf(stdout, "%s %lu\n< %s---\n> %s","Diferencia en linea", num_linea, linea1, linea2);
		}
	num_linea++;
	}

	while(leidos1 > 0){
		fprintf(stdout, "%s %lu\n< %s---\n>\n","Diferencia en linea", num_linea, linea1);
		leidos1 = getline(&linea1, &cant1, archivo1);
		num_linea++;
	}
	leidos2 = getline(&linea2, &cant2, archivo2);
	while(leidos2 > 0){
		fprintf(stdout, "%s %lu\n<\n---\n> %s","Diferencia en linea", num_linea, linea2);
		leidos2 = getline(&linea2, &cant2, archivo2);
		num_linea++;
	}

	free(linea1);
	free(linea2);
}

void procesar_archivos(char* nombre_archivo1, char* nombre_archivo2){

	FILE* archivo1 = fopen(nombre_archivo1, "r");

	if(!archivo1){
		fprintf(stderr, "%s\n", "Archivo erroneo");
		return;
	}

	FILE* archivo2 = fopen(nombre_archivo2, "r");

	if(!archivo2){
		fprintf(stderr, "%s\n", "Archivo erroneo");
		fclose(archivo1);
		return;
	}

	diff(archivo1, archivo2);

	fclose(archivo1);
	fclose(archivo2);
}

int main(int argc, char* argv[]){

	if(argc != 3){
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	}

	procesar_archivos(argv[1], argv[2]);

	return 0;
}