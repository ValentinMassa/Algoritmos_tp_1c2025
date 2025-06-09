#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/diccionario.h"
#include "PruebasKey.h"


typedef struct{
    int DNI;
    char name[25];
    int edad;
    char domicilio[50];
}t_personaDNI;


void imprimirPersonasDNI(const void* key, const void*dato);
int CompararClavesInt(const void*a , const void*b );


void pruebasKeyInt(){
    int cantidad = 15, i;
    puts("Prueba key INT");
    puts("----------------------------------------------------------");
    t_personaDNI auxdni;
    t_personaDNI auxPruebaBusquedaDNI = {30163456 ,"Agustin Navarro ESE", 38, "Castelli 303"};

    t_personaDNI vecv2[15] = {
        {30123456, "Juan Perez",      30, "Calle Falsa 123"},
        {27890123, "Ana Lopez",       25, "Av. Siempreviva 742"},
        {32567890, "Carlos Gomez",    40, "Mitre 456"},
        {30987654, "Lucia Fernandez", 22, "Belgrano 101"},
        {28765432, "Miguel Torres",   35, "San Martin 88"},
        {29876543, "Sofia Ramirez",   28, "Rivadavia 555"},
        {31456789, "Diego Suarez",    31, "Corrientes 789"},
        {27654321, "Valentina Diaz",  24, "Urquiza 12"},
        {31234567, "Martin Herrera",  29, "Sarmiento 73"},
        {29432109, "Camila Molina",   27, "Alsina 999"},
        {30321098, "Federico Castro", 33, "Maipú 64"},
        {28901234, "Julieta Rojas",   26, "Entre Rios 144"},
        {31678901, "Nicolas Aguirre", 32, "Santa Fe 321"},
        {27543210, "Laura Medina",    23, "Lavalle 201"},
        {30876543, "Agustin Navarro", 38, "Castelli 303"}};
    t_diccionario diccionario;

    crear_dic(&diccionario, 5, CompararClavesInt);
    for(i = 0; i<cantidad; i++){
        poner_dic(&diccionario, vecv2[i].name, sizeof(vecv2->name), &vecv2[i], sizeof(t_personaDNI));
    }
    ImprimirDiccionarioYColisiones(&diccionario, imprimirPersonasDNI);
    puts(" ");

    puts("PRUEBA DE OBTENER ELEMENTO");
    puts(" ");

    obtener_dic(&diccionario,vecv2[7].name, sizeof(vecv2->name), &auxdni, sizeof(auxdni));
    imprimirPersonasDNI(auxdni.name, &auxdni);
    obtener_dic(&diccionario,vecv2[12].name, sizeof(vecv2->name), &auxdni, sizeof(auxdni));
    imprimirPersonasDNI(auxdni.name, &auxdni);
    obtener_dic(&diccionario,vecv2[8].name, sizeof(vecv2->name), &auxdni, sizeof(auxdni));
    imprimirPersonasDNI(auxdni.name, &auxdni);

    puts("PRUEBA DE SACAR ELEMENTO");
    puts(" ");
    puts("SE SACA:");
    imprimirPersonasDNI(vecv2[10].name, &vecv2[10]);
    sacar_dic(&diccionario,vecv2[10].name, sizeof(vecv2->name));

    puts("SE SACA:");
    sacar_dic(&diccionario,vecv2[12].name, sizeof(vecv2->name));
    imprimirPersonasDNI(vecv2[12].name, &vecv2[12]);


    puts("SE SACA:");
    imprimirPersonasDNI(auxPruebaBusquedaDNI.name, &auxPruebaBusquedaDNI);
    sacar_dic(&diccionario,auxPruebaBusquedaDNI.name, sizeof(vecv2->name));

     puts("queda");
    ImprimirDiccionarioYColisiones(&diccionario, imprimirPersonasDNI);
    puts(" ");



    vaciar_dic(&diccionario);


    puts("FIN key INT");
    puts("----------------------------------------------------------");
}

//int
int CompararClavesInt(const void*a , const void*b ){
    int* ai = (int*)a;
    int* bi = (int*)b;

    return (*ai)-(*bi);
}


void imprimirPersonasDNI(const void* key, const void*dato){
    int* clave = (int*)key;
    t_personaDNI * per = (t_personaDNI*)dato;
    printf("CLAVE: %d, VALOR: %d %s, %d, %s \n", *clave, per->DNI, per->name, per->edad, per->domicilio);
}
