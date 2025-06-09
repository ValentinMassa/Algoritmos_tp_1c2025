#ifndef PROCESADORTEXTO_H_INCLUDED
#define PROCESADORTEXTO_H_INCLUDED

#include <string.h>

#define RutaGenerica "./ArchivoTexto/"
#define  MAX_LARGO_RUTA 47
#define  MAX_LARGO_ARCHIVO 50 - strlen(RutaGenerica)

typedef struct{
    unsigned TamTabla;
    char ruta[MAX_LARGO_RUTA];
}t_interfaz;

void InterfazUsuario();

#endif // PROCESADORTEXTO_H_INCLUDED
