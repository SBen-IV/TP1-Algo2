#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"

char caracter_cerrado(char signo){

	if(signo == '(') return ')';
	if(signo == '[') return ']';
	if(signo == '{') return '}';

	return '\0';
}

bool es_caracter_cerrado(char signo){

	if(signo == ')') return true;
	if(signo == ']') return true;
	if(signo == '}') return true;

	return false;
}

bool es_caracter_abierto(char signo){

	if(signo == '(') return true;
	if(signo == '[') return true;
	if(signo == '{') return true;

	return false;
}

bool es_par(char abierto, char cerrado){

	if(abierto == '(' && cerrado == ')') return true;
	if(abierto == '[' && cerrado == ']') return true;
	if(abierto == '{' && cerrado == '}') return true;

	return false;
}

bool validar_linea(char* linea){

	size_t i = 0, comilla_simple = 0;
	char buscado = '\0';
	pila_t* pila = pila_crear();

	if(!pila) return false;

	while(linea[i] != '\n'){
		if(es_caracter_abierto(linea[i]) && comilla_simple == 0){
			pila_apilar(pila, &linea[i]);
			buscado = caracter_cerrado(pila_ver_tope(pila));
		}else if(linea[i] == '\''){
			comilla_simple++;
			if(comilla_simple == 2){
				comilla_simple = 0;
				buscado = caracter_cerrado(pila_ver_tope(pila));
			}else{
				buscado = '\'';
			}
		}else if(es_caracter_cerrado(linea[i]) && comilla_simple == 0){
			if(!es_par(pila_desapilar(pila), linea[i])){
				pila_destruir(pila);
				return false;
			}
			buscado = caracter_cerrado(pila_ver_tope(pila));
		}
		i++;
	}

	if(buscado != '\0'){
		pila_destruir(pila);
		return false;
	}

	pila_destruir(pila);

	return true;
}

void syntax_val(){

	char* linea = NULL;
	size_t cant = 0;
	ssize_t leidos;

	while((leidos = getline(&linea, &cant, stdin) > 0)){
		if(validar_linea(linea)){
			fprintf(stdout, "%s\n", "OK");
		}else{
			fprintf(stdout, "%s\n", "ERROR");
		}
	}

	free(linea);
}

int main(){

	syntax_val();

	return 0;
}