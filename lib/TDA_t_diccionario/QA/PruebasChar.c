#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/diccionario.h"
#include "PruebasKey.h"

typedef struct{
    char name[25];
    int edad;
    char domicilio[50];

}t_persona;

int CompararClavesString(const void*, const void*);
void imprimirPersonas(const void* key, const void*dato);
void accionString(void* data);
void actualizarString(void* dataFin, const void* dataNueva);


void ProbarKeyChar(){
    int cantidad = 15, i;

    puts("Prueba key INT");
    puts("----------------------------------------------------------");
        t_persona aux;
    t_persona auxPruebaBusqueda = {"Agustin Navarro ESE", 38, "Castelli 303"};
    t_persona vec[15] = {
        {"Juan Perez", 30, "Calle Falsa 123"},
        {"Ana Lopez", 25, "Av. Siempreviva 742"},
        {"Carlos Gomez", 40, "Mitre 456"},
        {"Lucia Fernandez", 22, "Belgrano 101"},
        {"Miguel Torres", 35, "San Martin 88"},
        {"Sofia Ramirez", 28, "Rivadavia 555"},
        {"Diego Suarez", 31, "Corrientes 789"},
        {"Valentina Diaz", 24, "Urquiza 12"},
        {"Martin Herrera", 29, "Sarmiento 73"},
        {"Camila Molina", 27, "Alsina 999"},
        {"Federico Castro", 33, "Maipú 64"},
        {"Julieta Rojas", 26, "Entre Rios 144"},
        {"Nicolas Aguirre", 32, "Santa Fe 321"},
        {"Laura Medina", 23, "Lavalle 201"},
        {"Miguel Torres", 38, "Castelli 303"}};


    t_diccionario diccionario;
    crear_dic(&diccionario, 5, CompararClavesString);
    for(i = 0; i<cantidad; i++){
        poner_dicSinRep(&diccionario, vec[i].name, sizeof(vec->name), &vec[i], sizeof(t_persona), actualizarString);
    }
    ImprimirDiccionarioYColisiones(&diccionario, imprimirPersonas);
    puts(" ");

    puts("PRUEBA DE OBTENER ELEMENTO");
    puts(" ");

    obtener_dic(&diccionario,vec[7].name, sizeof(vec->name), &aux, sizeof(aux));
    imprimirPersonas(aux.name, &aux);
    obtener_dic(&diccionario,vec[13].name, sizeof(vec->name), &aux, sizeof(aux));
    imprimirPersonas(aux.name, &aux);
    obtener_dic(&diccionario,vec[9].name, sizeof(vec->name), &aux, sizeof(aux));
    imprimirPersonas(aux.name, &aux);

    puts("PRUEBA DE SACAR ELEMENTO");
    puts(" ");
    puts("SE SACA:");
    imprimirPersonas(vec[10].name, &vec[10]);
    sacar_dic(&diccionario,vec[10].name, sizeof(vec->name));

    puts("SE SACA:");
    sacar_dic(&diccionario,vec[12].name, sizeof(vec->name));
    imprimirPersonas(vec[12].name, &vec[12]);


    puts("SE SACA:");
    imprimirPersonas(auxPruebaBusqueda.name, &aux);
    sacar_dic(&diccionario,auxPruebaBusqueda.name, sizeof(vec->name));

    puts("queda");
    ImprimirDiccionarioYColisiones(&diccionario, imprimirPersonas);
    puts(" ");

    puts("Map + Hola");
    recorrer_dic_map(&diccionario, accionString);

    ImprimirDiccionarioYColisiones(&diccionario, imprimirPersonas);
    puts(" ");

    vaciar_dic(&diccionario);



    puts("FIN key CHAR");
    puts("----------------------------------------------------------");
}

//char
int CompararClavesString(const void*a , const void*b ){
    char* ai = (char*)a;
    char* bi = (char*)b;

    return strcmp(ai, bi);
}

void imprimirPersonas(const void* key, const void*dato){
    char* clave = (char*)key;
    t_persona * per = (t_persona*)dato;
    printf("CLAVE: %s, VALOR: %s, %d, %s \n", clave, per->name, per->edad, per->domicilio);
}

void accionString(void* data){
    t_persona* newperson = (t_persona*)data;
    strcat(newperson->name, " Hola");
}

void actualizarString(void* dataFin, const void* dataNueva){
    t_persona* finperson = (t_persona*)dataFin;
    t_persona* newperson = (t_persona*)dataNueva;

    finperson->edad = newperson->edad;
    strcpy(finperson->domicilio, newperson->domicilio);
}
