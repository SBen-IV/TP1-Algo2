#include <string.h>
#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 20
#define REDIMENSIONADOR 2
#define TAMANIO_RELATIVO 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    char* datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

bool redimensionar_pila(pila_t* pila, size_t tam_nuevo){

	char* datos_nuevos = realloc(pila->datos, tam_nuevo*sizeof(char));

	if(datos_nuevos == NULL){
		return false;
	}

	pila->datos = datos_nuevos;
	pila->capacidad = tam_nuevo;

	return true;
}

pila_t* pila_crear(void){

	pila_t* pila = malloc(sizeof(pila_t));

	if(!pila) return NULL;

	pila->datos = malloc(CAPACIDAD_INICIAL*sizeof(char*));

	if(pila->datos == NULL){
		free(pila);
		return NULL;
	}

	pila->cantidad = 0;
	pila->capacidad = CAPACIDAD_INICIAL;

	return pila;
}

void pila_destruir(pila_t *pila){

	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){

	return (pila->cantidad == 0);
}

bool pila_apilar(pila_t *pila, char* valor){

	if(pila->cantidad == pila->capacidad){
		size_t tam_nuevo = pila->capacidad*REDIMENSIONADOR;
		if(!redimensionar_pila(pila, tam_nuevo)){
			return false;
		}
	}

	pila->datos[pila->cantidad] = (*valor);

	pila->cantidad++;

	return true;
}

char pila_ver_tope(const pila_t *pila){

	if(pila_esta_vacia(pila)) return '\0';

	return pila->datos[pila->cantidad-1];
}

char pila_desapilar(pila_t *pila){

	if(pila_esta_vacia(pila)){
		return '\0';
	}
	if(pila->cantidad*TAMANIO_RELATIVO <= pila->capacidad){
		size_t tam_nuevo = pila->capacidad/REDIMENSIONADOR;
		redimensionar_pila(pila, tam_nuevo);
	}

	pila->cantidad--;

	return pila->datos[pila->cantidad];
}
