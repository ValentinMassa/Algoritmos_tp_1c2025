#include <stdio.h>
#include <stdlib.h>
#include "../headers/diccionario.h"
#include "../../TDA_t_ListaDiccionario/ListaDiccionario.h"

unsigned Hash_Generico_DJB2(const void* key, unsigned size_key, unsigned TamDiccionario);
//------------------------------------------------------------------------------------------------------

unsigned Hash_Generico_DJB2(const void* key, unsigned sizeKey, unsigned tabla_capacidad) {
    unsigned i;
    const unsigned char* p = key;

    unsigned long hash = 5381; //semilla inciial djb2, - colisiones en entradas reales, + (districucion uniforme numero primero impar)

    for (i = 0; i < sizeKey; i++) {
        hash = ((hash << 5) + hash) + p[i];  //hash << 5 multiplica el hasg por 2 a la 5, desplaza a la izq 5 bits.
    }
    return (unsigned)(hash % tabla_capacidad); //resultado entre 0 y tabla capacidad menos 1, ya que devuelve el resto
}

unsigned char crear_dic(t_diccionario * dic, int CapMax, int (*CmpDic)(const void* a, const void* b)){
    if(!CmpDic)
        return 0;

    t_DicLista * newl = (t_DicLista*)calloc(CapMax, sizeof(void*));
    if(!newl)
        return 0;

    dic->CmpDic = CmpDic;
    dic->dic = newl;
    dic->cantElem = CapMax;
    return 1;
}

unsigned char poner_dic(t_diccionario * dic, void* key, unsigned size_key , void* value, unsigned size_value){

    unsigned posicion;
    t_DicLista elemento;


    posicion = Hash_Generico_DJB2(key, size_key, dic->cantElem);

    if( dic->dic[posicion]  == 0){// primer valor en ese espacio del diccionario
        CreateDList(&elemento);
        if(!InsertarElementoEnElPrincipio(&elemento, key, size_key, value, size_value))
            return 0;
        dic->dic[posicion] = elemento;
    }
    else{
        if(!InsertarElementoEnElPrincipio(&(dic->dic[posicion]), key, size_key, value, size_value))
            return 0;
    }
    return 1;
}

unsigned char obtener_dic(t_diccionario * dic, void* key,unsigned size_key, void* data, unsigned size_data){

    unsigned posicion;
    posicion = Hash_Generico_DJB2(key, size_key, dic->cantElem);

    if(dic->dic[posicion] != 0) //existe la entrada a la tabla
    {
        if(!ObtenerValorPorClave( (&dic->dic[posicion]),key, data, size_data,dic->CmpDic))
            puts("No existe valor buscado");
    }
    else{
        puts("No existe esa entrada a la tabla");
        return 0; //no existe la entrada a la tabla, elemento no existe
    }
    return 1;
}

unsigned char sacar_dic(t_diccionario * dic, const void* key, unsigned size_key){
    unsigned posicion;
    posicion = Hash_Generico_DJB2(key, size_key, dic->cantElem);

    if(dic->dic[posicion] != 0) //existe la entrada a la tabla
    {
        if(!EliminarValorPorClave(&dic->dic[posicion], key, dic->CmpDic))
            puts("No existe esa clave");
    }
    else{
        puts("No existe esa entrada a la tabla");
        return 0; //no existe la entrada a la tabla, elemento no existe
    }


    return 1;


}

void recorrer_dic_map(t_diccionario * dic, void accion(void* data)){
    int i;

    for(i=0; i<dic->cantElem; i ++){
        if(dic->dic[i] != 0)
            MapDLista(( &dic->dic[i]), accion);
    }
}

void vaciar_dic(t_diccionario * dic){

    int i;
    for(i=0; i<dic->cantElem; i ++){
        if(dic->dic[i] != 0)
            EliminarDlista(&dic->dic[i]);
    }
}


void ImprimirDiccionarioYColisiones(t_diccionario * dic, void (*imprimir)(const void*clave, const void* valor)){
    int i;
    for(i=0; i<dic->cantElem; i ++){
        printf("Posicion de tabla: %d / Numero Memoria: %p \n", i, (void*)&(dic->dic[i]));
        if(dic->dic[i] != 0)
            imprimirDLista(&dic->dic[i], imprimir);
    }
}
