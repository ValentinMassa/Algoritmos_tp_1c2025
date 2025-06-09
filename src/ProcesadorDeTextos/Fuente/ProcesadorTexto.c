#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header/ProcesadorTexto.h"

void InterfazUsuario(){
    char nombre_archivo[MAX_LARGO_ARCHIVO];
    char ruta[MAX_LARGO_RUTA];
    FILE* fp;
    t_interfaz newI;
    int valido;

    printf("=================================================\n");
    printf("||     BIENVENIDO AL PROCESADOR DE TEXTO CON   ||\n");
    printf("||                SISTEMA HASH                 ||\n");
    printf("=================================================\n\n");

    do {
        memset(ruta,0,sizeof(newI.ruta));
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
        strcpy(ruta, RutaGenerica);
        strcat(ruta, nombre_archivo);

        fp = fopen(ruta, "rt");
        if (!fp) {
            printf("> No se pudo abrir el archivo en la ruta: %s\n", newI.ruta);
            puts("Intente nuevamente...\n");
            valido = 0;
        } else {
            valido = 1;
        }
    } while (!valido);
    fclose(fp);
    printf("> Ingrese la cantidad de entradas de la tabla: ");
    while (scanf("%u", &newI.TamTabla) != 1 || newI.TamTabla == 0) {
        printf("Cantidad inválida. Ingrese un número mayor a 0: ");
        fflush(stdin);
    }
    fflush(stdin);

    printf("\n> ¡Datos cargados correctamente!\n");
    printf("> Archivo: %s\n", newI.ruta);
    printf("> Tamaño de la tabla: %u\n", newI.TamTabla);

}
