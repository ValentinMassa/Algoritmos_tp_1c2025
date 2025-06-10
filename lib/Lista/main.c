#include "./main.h"
#include <stdlib.h>
#include <string.h>

int CantidadNodosRec(Slist * l);

void createList(Slist * _list)
{
    *_list = NULL;
}

int isFullList(Slist *_list,unsigned sizeData)
{
    Node * auxNode = (Node*)malloc(sizeof(Node)) ;
    void* auxData = malloc(sizeData);

    free(auxNode);
    free(auxData);

    return auxNode == NULL || auxData == NULL;
}

int isEmptyList(Slist *_list)
{
    return *_list == NULL;
}


int InsertWithNoRepeatedInList(Slist *_list, void* data, unsigned sizeData, cmp CMP, action ACTION )
{
    Node * auxNode;

    while( *(_list) )
    {
        if( CMP( (*_list)->data, data) == 0)
        {
            if(ACTION)
                ACTION((*_list)->data, data);
            return 1;
        }
        _list = &(*_list)->next;
    }

    if( (auxNode = (Node*)malloc(sizeof(Node))) == NULL ||
                    (auxNode->data = malloc(sizeData)) == NULL )
    {
        free(auxNode);
        return 0;
    }

    memcpy(auxNode->data, data, sizeData);
    auxNode->sizeData = sizeData;
    auxNode->next = NULL;
    *_list = auxNode;

    return 1;
}


void printList(Slist *_list, void* pf, void(*showList)(const void * data, void* file))
{
    while(*_list)
    {
        showList((*_list)->data, pf);
        _list = &(*_list)->next;
    }
    return;
}

void printListTop(Slist *l, void* param ,void(*showList)(const void * data, void* param),
                  int (*cmp)(const void *a, const void*b))
{
    int cont = 1;
    int band = 0;

    while(*l)
    {
        if(band == 0)printf("\t\t TOP: %d \n", cont);
        showList((*l)->data, param);

        if( (*l)->next &&  (cmp( (*l)->data, (*l)->next->data) == 0) ){
            l = &(*l)->next;
            band = 1;
            continue;
        }
        band = 0;
        cont ++;
        l = &(*l)->next;
    }
    return;
}



int getFirstElement(Slist * _list, void* data, unsigned sizeData)
{
    Node * nodeaux;

    if(!*_list)return 0;

    nodeaux = (*_list);
    (*_list) = nodeaux->next;

    memcpy(data, nodeaux->data, MIN(nodeaux->sizeData, sizeData));

    free(nodeaux->data);
    free(nodeaux);


    return 1;

}
void destroyList(Slist* _list)
{
    Node* nodeaux;

    while(*_list)
    {
        nodeaux = *_list;
        *_list = nodeaux->next;
        free(nodeaux->data);
        free(nodeaux);
    }

}

int InsertarMaxNElementosEnOrden(Slist * l, void* data, unsigned sized, int n,
                           int(*cmp)(const void*, const void*)){
    int resultado;
    int cantNodos = CantidadNodosRec(l);
    Node *nuevo;
    Node **ultimo;

    while( (*l) && (resultado = cmp( (*l)->data ,data)) >= 0) //A - B = 4 - 5 = -1
        l = &(*l)->next;

    if(!*l && cantNodos == n )return 1;

    if(cantNodos == n){
        ultimo = l;
        while( (*ultimo)->next) ultimo = &(*ultimo)->next;
        free((*ultimo)->data);
        free((*ultimo));
        (*ultimo) = NULL;
    }
    if( (nuevo = (Node*)malloc(sizeof(Node))) == NULL ||(nuevo->data = malloc(sized)) == NULL ){
            free(nuevo);
            return 0;
            }
    memcpy(nuevo->data, data, sized);
    nuevo->sizeData = sized;
    nuevo->next = (*l);
    (*l) = nuevo;
    return 1;
}




int CantidadNodosRec(Slist * l){
    int cant = 0;

    if(!(*l)) return 0;

    cant = CantidadNodosRec(&(*l)->next);

    return cant + 1;
}
