#include <stdlib.h>
#include <stdio.h> // sprintf
#include "fraccion.h"

struct fraccion
{
    /* data */
    int numerador;
    int denominador;
};

void simplificar_fraccion(fraccion_t *fraccion);
size_t largo_numero(int num);
int valor_absoluto(int n);
int obtener_maximo(int valor1, int valor2);


fraccion_t* fraccion_crear(int numerador, int denominador){
    
    if (denominador == 0) return NULL;
    
    fraccion_t *fraccion = malloc( sizeof(fraccion_t) );

    if (!fraccion) return NULL;

    if ( numerador * denominador < 0 && denominador < 0 ){
        /*pasamos el menos al numerador*/
        numerador *= (-1);
        denominador *= (-1);
    }

    if ( denominador < 0 && numerador < 0 ){
        denominador *= (-1);
        numerador *=(-1);
    }

    fraccion->denominador = denominador;
    fraccion->numerador = numerador;

    return fraccion;
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2){

    int denominador = f1->denominador * f2->denominador;
    int numerador = f1->numerador * f2->denominador + f2->numerador * f1->denominador;

    fraccion_t *sumar_fraccion = fraccion_crear(numerador, denominador);

    if (!sumar_fraccion) return NULL;

    fraccion_destruir(f1);
    fraccion_destruir(f2);

    return sumar_fraccion;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2){

    int denominador = f1->denominador * f2->denominador;
    int numerador = f1->numerador * f2->numerador ;

    fraccion_t *mul_fraccion = fraccion_crear(numerador, denominador);

    if (!mul_fraccion) return NULL;

    fraccion_destruir(f1);
    fraccion_destruir(f2);

    return mul_fraccion;
}

int fraccion_parte_entera(fraccion_t* fraccion){
    return fraccion->numerador/ fraccion->denominador;
}

void fraccion_destruir(fraccion_t* fraccion){
    free(fraccion);
}

char* fraccion_representacion(fraccion_t* fraccion){

    simplificar_fraccion(fraccion);

    int es_negativo = fraccion->denominador * fraccion->numerador < 0 ? 1 : 0;
    int es_fraccion = fraccion->denominador > 1 ? 1 : 0;

    size_t largo_denominador = es_fraccion ? largo_numero(fraccion->denominador) : 0 ;
    size_t largo_numerador = largo_numero(fraccion->numerador);
    size_t tamanio = largo_numerador + largo_denominador + es_negativo + es_fraccion + 1;

    char *representacion_fraccion = calloc(tamanio , sizeof(char));

    if (!representacion_fraccion) return NULL;

    if ( !es_fraccion ){
        sprintf(representacion_fraccion, "%d", fraccion->numerador);
    }else{
        sprintf(representacion_fraccion,"%d/%d", fraccion->numerador, fraccion->denominador);
    }

    return representacion_fraccion;
}

void simplificar_fraccion(fraccion_t *fraccion){

    int valorMaximo = obtener_maximo(fraccion->numerador, fraccion->denominador);

    for (int i=2; i < valorMaximo; i++){
        
        while ( fraccion->numerador % i == 0 && fraccion->denominador % i == 0 ){
            fraccion->numerador /= i;
            fraccion->denominador /= i;
        }
    }
}

int obtener_maximo(int valor1, int valor2){
    int a = valor_absoluto(valor1);
    int b = valor_absoluto(valor2);
    return a >= b ? a : b;
}

int valor_absoluto(int n){
    return n < 0 ? n*(-1) : n ;
}

size_t largo_numero(int num) {
    int n = valor_absoluto(num);
	if (n == 0) {
		return 1;
	}
	size_t cant = 0;
	while (n > 0) {
		cant++;
		n /= 10;
	}
	return cant;
}

/*
https://github.com/tomasaccini/valgreen
*/
