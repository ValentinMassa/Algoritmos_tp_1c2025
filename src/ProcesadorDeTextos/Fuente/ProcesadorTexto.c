#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Header/ProcesadorTexto.h"
#include "../../../lib/TDA_t_diccionario/headers/diccionario.h"
#include "../../../lib/Lista/main.h"

#define TAM_MAX_BUFFER 1000
#define TAM_MAX_WORD 15
#define CANT_ELEM_TOP 5

#define ES_ESPACIO(a)( (a) == ' '? 1:0)

#define ES_SIGNO_PUNTUACION(c) ( \
    (c) == '.' || (c) == ',' || (c) == ';' || (c) == ':' || \
    (c) == '!' || (c) == '?' || (c) == '(' || (c) == ')' || \
    (c) == '[' || (c) == ']' || (c) == '{' || (c) == '}' || \
    (c) == '"' || (c) == '\''|| (c) == '-' || (c) == '—' || \
    (c) == '…' || (c) == '`' )

#define ES_LETRA(c) ( ((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z') )



typedef struct{
    unsigned TamTabla;
    char ruta[MAX_LARGO_RUTA];
}t_interfaz;

typedef struct{
    char palabra[TAM_MAX_WORD];
    unsigned repeticion;
}t_palabra;

typedef struct{
    unsigned cantPalabras;
    unsigned cantEspacios;
    unsigned cantidadSignosPuntuacion;
}t_informe;



void interfazCargaDatosIniciales(t_interfaz * newI);
unsigned char InterfazOperaciones(t_interfaz * newI);
unsigned char CargarArchivoEnDiccionario(t_interfaz * newI, t_diccionario *diccionario, t_informe * informe);
        int CompararClavesString(const void*a , const void*b );
    unsigned char TrozarYGuardarPalabras(char* buffer, t_diccionario* diccionario, t_informe * informe);
        char* BuscarInicioPalabraRecursivo(char*fin, char* buffer);
        void ponerEnMayuscula(char* palabra) ;
    void ActualizarCantidadRepeticiones(void*a, const void*b);
    void imprimirPalabras(const void* key, const void*dato);
    void MejoresPalabras(void*data, void* param);
        int cmpNumeros(const void* a, const void* b);
        void imprimirTopPalabras(const void* data, void* param);


void InterfazUsuario(){
    t_interfaz newI;
    interfazCargaDatosIniciales(&newI);
    InterfazOperaciones(&newI);
}

void interfazCargaDatosIniciales(t_interfaz * newI){
    char nombre_archivo[MAX_LARGO_ARCHIVO];
    FILE* fp;
    int valido;

    printf("=================================================\n");
    printf("||     BIENVENIDO AL PROCESADOR DE TEXTO CON   ||\n");
    printf("||                SISTEMA HASH                 ||\n");
    printf("=================================================\n\n");

    do {
        memset(newI->ruta,0,sizeof(newI->ruta));
        printf("> Ingrese el nombre del archivo (.txt): ");
        if (fgets(nombre_archivo, MAX_LARGO_ARCHIVO, stdin) == NULL) {
            fprintf(stderr, "Error al leer el nombre del archivo.\n");
            continue;
        }
        nombre_archivo[strcspn(nombre_archivo, "\n")] = '\0';

        if (strstr(nombre_archivo, ".txt") == NULL) {
            fprintf(stderr, "El archivo debe tener extension .txt\n");
            continue;
        }
        strcpy(newI->ruta, RutaGenerica);
        strcat(newI->ruta, nombre_archivo);

        fp = fopen(newI->ruta, "rt");
        if (!fp) {
            printf("> No se pudo abrir el archivo en la ruta: %s\n", newI->ruta);
            puts("Intente nuevamente...\n");
            valido = 0;
        } else {
            valido = 1;
        }
    } while (!valido);
    fclose(fp);
    printf("> Ingrese la cantidad de entradas de la tabla: ");
    while (scanf("%u", &newI->TamTabla) != 1 || newI->TamTabla == 0) {
        printf("Cantidad inválida. Ingrese un número mayor a 0: ");
        fflush(stdin);
    }
    fflush(stdin);

    printf("\n> Datos cargados correctamente!\n");
    printf("> Archivo: %s\n", newI->ruta);
    printf("> Tamanio de la tabla: %u\n", newI->TamTabla);
}

unsigned char InterfazOperaciones(t_interfaz * newI){
    char opcion[5];
    int opcionFin;
    Slist lista;

    t_informe informe =
        {
            .cantEspacios = 0,
            .cantPalabras = 0,
            .cantidadSignosPuntuacion = 0
        };

    t_diccionario diccionario;
    if(!CargarArchivoEnDiccionario(newI, &diccionario, &informe)){
        puts("Error inesperado");
        vaciar_dic(&diccionario);
        return 0;
    }

    printf("=================================================\n");
    printf("||      PROCESADOR DE TEXTO CON                ||\n");
    printf("||            SISTEMA HASH                     ||\n");
    printf("===============================================\n\n");
    printf("> Seleccione una opcion para operar con el archivo: \n \t\t > %s \n", newI->ruta);

    do{
    printf("> 0. Informe (cantidad de palabras, espacios y signos de puntuación que contiene el texto) \n");
    printf("> 1. Podio top 5 palabras mas utilizadas \n");
    printf("> 2. Ver Tabla Hash Key y Valores \n");
    printf("> 3. Salir \n");
    printf("> Ingrese su opcion: ");
        fflush(stdin);
        if (fgets(opcion, sizeof(opcion), stdin) == NULL) {
        printf("\n> La opcion NO se encuentra disponible. Intente de nuevamente.\n");
        *opcion = '0';
        continue;
        }
        opcionFin = atoi(opcion);

        switch (opcionFin) {
            case 0:
                printf("\n> Mostrando informe...\n");
                printf("CANTIDAD PALABRAS: %d \nCANTIDAD ESPACIOS: %d\nCANTIDAD SIGNOS DE PUNTUACION: %d\n",
                           informe.cantPalabras, informe.cantEspacios, informe.cantidadSignosPuntuacion);
                break;
            case 1:
                createList(&lista);
                recorrer_dic_map(&diccionario, &lista, MejoresPalabras);
                printf("\n> Mostrando top 5 palabras mas utilizadas...\n");
                printListTop(&lista, NULL,imprimirTopPalabras,cmpNumeros);
                destroyList(&lista);
                break;

            case 2:
                printf("\n> Mostrando la tabla hash...\n");
                    ImprimirDiccionarioYColisiones(&diccionario,imprimirPalabras);
                break;

            case 3:
                printf("\n> Saliendo del programa...\n");
                break;

            default:
                printf("\n> Opción no válida. Intente nuevamente.\n");
                break;
        }

        if (opcionFin != 3) {
            printf("\n> Presione ENTER para continuar...");
            getchar();  // Espera ENTER
        }
        fflush(stdin);
    }while (opcionFin != 3);

    vaciar_dic(&diccionario);

    return 1;
}

void MejoresPalabras(void*data, void* param){
    t_palabra * palabra = (t_palabra*)data;
    Slist * lista = (Slist*)param;
    InsertarMaxNElementosEnOrden(lista, palabra,sizeof(t_palabra), CANT_ELEM_TOP, cmpNumeros);
}


int cmpNumeros(const void* a, const void* b){
    t_palabra * ai = (t_palabra*)a;
    t_palabra * bi = (t_palabra*)b;

    return (ai->repeticion - bi->repeticion);
}

unsigned char CargarArchivoEnDiccionario(t_interfaz * newI, t_diccionario *diccionario, t_informe * informe){
    FILE *fp;
    char buffer[TAM_MAX_BUFFER];

    crear_dic(diccionario, newI->TamTabla, CompararClavesString);

    fp = fopen(newI->ruta, "rt");
    if(!fp)
        return 0;

    while(fgets(buffer, TAM_MAX_BUFFER, fp) != NULL){
            if(*buffer == '\n')continue;
        if(!TrozarYGuardarPalabras(buffer, diccionario, informe)){
            puts("ERROR INESPERADO EN EL TROZADO");
            fclose(fp);
            return 0;
        }
    }
    return 1;
    fclose(fp);
}

unsigned char TrozarYGuardarPalabras(char* buffer, t_diccionario* diccionario, t_informe * informe){
    t_palabra palabra;

    char* pointer = buffer, *inicio, *fin;

    pointer = strchr(buffer, '\n');
    if(pointer){
       *pointer = '\0';
    }
    pointer = strchr(buffer, '\0');
    pointer --;

    while(pointer >= buffer){
        if(ES_ESPACIO(*pointer)){
            informe->cantEspacios +=1;
            *pointer = '\0';
            pointer --;
            continue;
        }
        if(ES_SIGNO_PUNTUACION(*pointer)){
            informe->cantidadSignosPuntuacion += 1;
            *pointer = '\0';
            pointer --;
            continue;
        }
        //una palabra se comprende entre dos letras
        fin = pointer;
        inicio = BuscarInicioPalabraRecursivo(fin, buffer);

        memset(palabra.palabra, 0, TAM_MAX_WORD);
        strcpy(palabra.palabra, inicio);
        palabra.repeticion = 0;

        if(!poner_dicSinRep(diccionario, palabra.palabra,TAM_MAX_WORD,&palabra, sizeof(palabra), ActualizarCantidadRepeticiones))
            return 0;
        informe->cantPalabras +=1;
        *inicio = '\0';
        pointer = inicio - 1;
    }
    return 1;
}

char* BuscarInicioPalabraRecursivo(char*fin, char* buffer){
    char* iterador;

    if(fin<= buffer) return buffer;

    iterador = fin - 1;

    if(ES_ESPACIO(*iterador) || ES_SIGNO_PUNTUACION(*iterador))
        return iterador + 1;

    return BuscarInicioPalabraRecursivo(iterador, buffer);
}
void imprimirTopPalabras(const void* data, void* param){
    t_palabra * palabra = (t_palabra*)data;
    printf("PALABRA: %s REPETICIONES: %d \n", palabra->palabra, palabra->repeticion);
}

void ActualizarCantidadRepeticiones(void*a, const void*b){
    t_palabra * viejo = (t_palabra*)a;
    viejo->repeticion += 1;
}

int CompararClavesString(const void*a , const void*b ){
    char* ai = (char*)a;
    char* bi = (char*)b;

    return strcmp(ai, bi);
}

void imprimirPalabras(const void* key, const void*dato){
    char* clave = (char*)key;
    t_palabra * palabra = (t_palabra*)dato;
    printf("CLAVE: %s, VALOR: PALABRA: %s REPETICIONES: %d \n", clave, palabra->palabra, palabra->repeticion);
}

void ponerEnMayuscula(char* palabra) {
    while (*palabra) {
        *palabra = toupper((unsigned char)*palabra);
        palabra++;
    }
}
