#ifndef LIST__MAIN_H_INCLUDED
#define LIST__MAIN_H_INCLUDED

#include <stdio.h>

#define MIN(X, Y) ((X) < (Y)? X:Y)

#ifndef node
#define node
    typedef struct Node{
        void* data;
        unsigned sizeData;
        struct Node *next;
    }Node;
#endif // node

typedef Node * Slist;


typedef int(*cmp)(const void*a, const void*b);
typedef void (*action)(void *a, const void* b);

int InsertWithNoRepeatedInList(Slist *_list, void* data, unsigned sizeData, cmp CMP, action ACTION );
int isEmptyList(Slist *_list);
int isFullList(Slist *_list, unsigned sizeData);
void createList(Slist * _list);
int getFirstElement(Slist * _list, void* data, unsigned sizeData);
void destroyList(Slist* _list);
int InsertarMaxNElementosEnOrden(Slist * l, void* data, unsigned sized, int n,
                           int(*cmp)(const void*, const void*));
void printListTop(Slist *l, void* param ,void(*showList)(const void * data, void* param),
                  int (*cmp)(const void *a, const void*b));

void printList(Slist *_list, void* pf, void(*showList)(const void * data, void* file));
#endif // MAIN_H_INCLUDED
