#include <stdlib.h>
#include <assert.h>
#define throw(MSG) assert(0 && MSG)
#include <listNode.h>
#include <list.h>
struct List {
        ListNode *head;
};
// DONE
List *List_new(void){
        List *list = (List *)malloc(sizeof(List));
        list->head = NULL;
        return list;
}
// DONE
void List_free(List **self, void (*dataFree)(void *)){
        if(self != NULL) {
                if((*self)->head != NULL) {
                        ListNode_freeAll(&(*self)->head, dataFree);
                }
                free(*self);
                *self = NULL;
        }
}
// DONE
void List_addFirst(List *self, void *data){
        self->head = ListNode_addBefore(self->head, ListNode_new(data));
}
// DONE
void List_addLast(List *self, void *data){
        if(self->head == NULL) {
                List_addFirst(self, data);
                return;
        }
        ListNode *curr = self->head;
        while(ListNode_getNext(curr) != NULL) {
                curr = ListNode_getNext(curr);
        }

        ListNode_addAfter(curr, ListNode_new(data));
}

void *List_removeFirst(List *self){
        if(self->head == NULL) throw("List_removeFirst: list == null\n");
        return ListNode_remove(self->head, 0);
}

int List_getLength(List *self){
        return ListNode_getLength(self->head);
}

void *List_getDataAt(List *self, int index){
        return ListNode_getData(ListNode_getNodeAt(self->head, index));
}
