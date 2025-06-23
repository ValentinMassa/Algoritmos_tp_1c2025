#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDiccionario.h"

#define minimo(a,b)((a) < (b)?(a):(b))


void CreateDList(t_DicLista *p){
    *p = NULL;
}
unsigned char InsertarElementoEnElPrincipio(t_DicLista *p, const void* key, unsigned sizeKey, const void* Data, unsigned sizeData){
    t_Node * nuevo;

    nuevo = (t_Node*)malloc(sizeof(t_Node));
    if(!nuevo)return 0;

    if(( nuevo->__key = malloc(sizeKey)) == NULL || (nuevo->__data = malloc(sizeData)) == NULL) {
        free(nuevo->__key);
        free(nuevo);
        return 0;
       }
    memcpy(nuevo->__key, key, sizeKey);
    nuevo->__sizeKey = sizeKey;

    memcpy(nuevo->__data, Data, sizeData);
    nuevo->__Size_Data = sizeData;
    nuevo->__next = *p;
    *p = nuevo;
    return 1;
    }

unsigned char InsertarElementoSinRepeticionDeKey(t_DicLista *p, const void* key, unsigned sizeKey, const void* Data, unsigned sizeData,
                                            void(*actualizar)(void*a, const void* b), int (*CmpDic)(const void* a, const void* b)){
    t_Node * nuevo;
    int resultado = 1;

    while( *p && ( resultado = CmpDic(key, (*p)->__key) ) != 0 )
        p = &(*p)->__next;

    if(resultado == 0){
        actualizar((*p)->__data, Data);
        return 1;
    }

    nuevo = (t_Node*)malloc(sizeof(t_Node));
    if(!nuevo)return 0;
    
    if(( nuevo->__key = malloc(sizeKey)) == NULL || (nuevo->__data = malloc(sizeData)) == NULL) {
        free(nuevo->__key);
        free(nuevo);
        return 0;
       }
    memcpy(nuevo->__key, key, sizeKey);
    nuevo->__sizeKey = sizeKey;

    memcpy(nuevo->__data, Data, sizeData);
    nuevo->__Size_Data = sizeData;

    nuevo->__next = *p;
    *p = nuevo;
    return 1;
}

unsigned char ObtenerValorPorClave(t_DicLista *p, const void* key, void* DestinoData,
                                   unsigned sizeDataDestino,
                                   int (*CmpDic)(const void* a, const void* b)){
    int resultado = 1;

    while( *p && (resultado = CmpDic((*p)->__key, key) ) != 0 )
    {
        p = &(*p)->__next;
    }

    if( resultado == 0)
    {
        memcpy(DestinoData, (*p)->__data, minimo(sizeDataDestino, (*p)->__Size_Data) );
        return 1;
    }
    return 0;
}

unsigned char EliminarValorPorClave(t_DicLista *p, const void* key,
                                   int (*CmpDic)(const void* a, const void* b)){
    int resultado = 1;
    t_Node * elim;

    while( *p && (resultado = CmpDic( (*p)->__key, key)) != 0 )
    {
        p = &(*p)->__next;
    }

    if( resultado == 0)
    {
        elim = (*p);
        (*p) = elim->__next;
        free(elim->__data);
        free(elim->__key);
        free(elim);
        return 1;
    }
    return 0;
}
void MapDLista(t_DicLista *p, void* param ,void (*accion)(void* dataNodo, void* parametro)){
    while(*p){
        accion((*p)->__data, param);
        p = &(*p)->__next;
    }
}

void EliminarDlista(t_DicLista *p){
    t_Node* elim;

    while(*p){
        elim = (*p);
        (*p) = elim->__next;
        free(elim->__data);
        free(elim->__key);
        free(elim);
    }
}


void imprimirDLista(t_DicLista *p, void (*imprimirVyD)(const void*, const void*)){
    int i = 0;
    while(*p){
        printf("\t\t %i: ", i);
        imprimirVyD( (*p)->__key, (*p)->__data );
        p = &(*p)->__next;
        i++;
    }
}
