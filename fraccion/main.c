#include <stdlib.h>
#include <stdio.h> // sprintf
#include "fraccion.h"

void* test(void);


int main(){

    test();
    return 0;
}


void* test(){
    fraccion_t* f = fraccion_crear(-2*3*4,2*3*5);
    
    if (!f){
        printf("Ah ocurrido un error\n");
        return NULL;   
    }
    
    char* rep = fraccion_representacion(f);
    
    printf("%s \n", rep);
    
    fraccion_destruir(f);
    free(rep);
    
    return NULL;
}

