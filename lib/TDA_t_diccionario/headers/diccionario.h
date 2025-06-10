#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

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

typedef struct{
    unsigned cantElem;
    t_DicLista * dic;
    int (*CmpDic)(const void* a, const void* b);
}t_diccionario;


unsigned char crear_dic(t_diccionario * dic, int CapMax, int(*CmpDic)(const void* a, const void* b)); //recibe el tda diccionario, la cant elem, y el cmp de los datos

unsigned char poner_dic(t_diccionario * dic, void* key, unsigned size_key , void* value, unsigned size_value);

unsigned char poner_dicSinRep(t_diccionario * dic, void* key, unsigned size_key , void* value, unsigned size_value, void (*actualizar)(void*, const void*));

unsigned char obtener_dic(t_diccionario * dic, void* key,unsigned size_key, void* data, unsigned size_data);


unsigned char sacar_dic(t_diccionario * dic, const void* key, unsigned size_key);

void recorrer_dic_map(t_diccionario * dic, void* param , void accion(void* data, void* parametro));

void vaciar_dic(t_diccionario * dic);

void ImprimirDiccionarioYColisiones(t_diccionario * dic, void (*imprimir)(const void*clave, const void* valor));

#endif // DICCIONARIO_H_INCLUDED



