#include <stdlib.h>
#include "cola.h"

typedef struct nodo{
	void* dato;
	struct nodo* proximo;
}nodo_t;

struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};

cola_t* cola_crear(void){

	cola_t* cola = malloc(sizeof(cola_t));

	if(!cola){
		return NULL;
	}

	cola->primero = cola->ultimo = NULL;

	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){

	void* dato;

	while(!cola_esta_vacia(cola)){
		dato = cola_desencolar(cola);
		if(destruir_dato){
			destruir_dato(dato);
		}
	}

	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){

	return (!cola->primero && !cola->ultimo);
}

bool cola_encolar(cola_t *cola, void* valor){

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));

	if(!nodo_nuevo) return false;

	nodo_nuevo->dato = valor;
	nodo_nuevo->proximo = NULL;

	if(cola_esta_vacia(cola)){
		cola->primero = nodo_nuevo;
	}else{
		cola->ultimo->proximo = nodo_nuevo;
	}

	cola->ultimo = nodo_nuevo;

	return true;
}

void* cola_ver_primero(const cola_t *cola){

	if(cola_esta_vacia(cola)) return NULL;

	return cola->primero->dato;
}

void* cola_desencolar(cola_t *cola){

	if(cola_esta_vacia(cola)) return NULL;

	nodo_t* nodo_aux;
	void* dato;

	nodo_aux = cola->primero;
	dato = cola->primero->dato;
	cola->primero = cola->primero->proximo;

	free(nodo_aux);

	if(cola->primero == NULL){
		cola->ultimo = NULL;
	}

	return dato;
}