#ifndef LISTADICCIONARIO_H_INCLUDED
#define LISTADICCIONARIO_H_INCLUDED

#ifndef LISTA_DIC
#define LISTA_DIC
typedef struct sNode{
    void * __key;
    unsigned __sizeKey;
    void* __data;
    unsigned __Size_Data;
    struct sNode * __next;
}t_Node;

typedef t_Node * t_DicLista;
#endif

void CreateDList(t_DicLista *p);

unsigned char InsertarElementoEnElPrincipio(t_DicLista *p, const void* key, unsigned sizeKey, const void* Data, unsigned sizeData);

unsigned char ObtenerValorPorClave(t_DicLista *p, const void* key, void* DestinoData,
                                   unsigned sizeDataDestino,
                                   int (*CmpDic)(const void* a, const void* b));

unsigned char EliminarValorPorClave(t_DicLista *p, const void* key, int (*CmpDic)(const void* a, const void* b));

void MapDLista(t_DicLista *p, void (*accion)(void*));

void EliminarDlista(t_DicLista *p);

void imprimirDLista(t_DicLista *p, void (*imprimirVyD)(const void*, const void*));



#endif // LISTADICCIONARIO_H_INCLUDED
