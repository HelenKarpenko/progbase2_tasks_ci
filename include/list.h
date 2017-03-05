#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct List List;

List *List_new(void);
void List_free(List **self, void (*dataFree)(void *));
void List_addFirst(List *self, void *data);
void List_addLast(List *self, void *data);
void *List_removeFirst(List *self);
void *List_getDataAt(List *self, int index);
int List_getLength(List * list );

#endif
