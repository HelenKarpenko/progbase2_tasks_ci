#include <stdlib.h>
#include <assert.h>
#include "../../include/listNode.h"
#define throw(MSG) assert(0 && MSG)

struct ListNode {
        void *data;
        ListNode *next;
};

// DONE
ListNode *ListNode_new(void *data){
        ListNode *listNode = (ListNode *)malloc(sizeof(ListNode));
        if(listNode == NULL) {
                return NULL;
        }
        listNode->data = data;
        listNode->next = NULL;
        return listNode;
}
// DONE
void ListNode_free(ListNode **self, void (*dataFree)(void *)){
        if(self == NULL) {
                throw("ListNode == NULL\n");
        }
        if(dataFree != NULL) {
                dataFree((*self)->data);
        }
        free(*self);
        *self = NULL;
}

// DONE
void ListNode_freeAll(ListNode **self, void (*dataFree)(void *)){
        if(self != NULL) {
                ListNode *curr = *self;
                ListNode *tmp;
                while(curr != NULL) {
                        tmp = curr->next;
                        ListNode_free(&curr, dataFree);
                        curr = tmp;
                }
        }
}

// DONE
void *ListNode_getData(ListNode *self){
        if(self == NULL) throw("ListNode_getData: ListNode = NULL\n");
        return self->data;
}

// DONE
ListNode *ListNode_getNext(ListNode *self){
        if(self == NULL) throw("ListNode_getNext: ListNode = NULL\n");
        return self->next;
}

// DONE
ListNode *ListNode_addAfter(ListNode *self, ListNode *addNode){
        if(addNode == NULL) throw("ListNode_addAfter: addNode = NULL\n");
        if(self == NULL) return addNode;
        addNode->next = self->next;
        self->next = addNode;
        return self;
}

// DONE
ListNode *ListNode_addBefore(ListNode *self, ListNode *addNode){
        if(addNode == NULL) throw("ListNode_addBefore: addNode = NULL\n");
        if(self == NULL) return addNode;
        addNode->next = self;
        return addNode;
}

// DONE
ListNode *ListNode_remove(ListNode *self, int index){
        if(index < 0) throw("ListNode_remove: index < 0\n");
        if(self == NULL) throw("ListNode_remove: ListNode = NULL\n");
        if(index == 0) {
                ListNode *tmp = self->next;
                ListNode_free(&self, NULL);
                return tmp;
        }
        ListNode *curr = self;
        int i = 1;
        while(curr->next != NULL && i != index) {
                curr = curr->next;
                i++;
        }
        if(i != index) throw("Невирный индекс\n");
        if(curr->next != NULL) {
                ListNode *tmp = curr->next->next;
                ListNode_free(&curr->next, NULL);
                curr->next = tmp;
        }else{
                ListNode_free(&(curr->next), NULL);
        }
        return self;
}
// DONE
ListNode *ListNode_getNodeAt(ListNode *self, int index){
        if(index < 0) throw("ListNode_getNodeAt: index < 0\n");
        if(self == NULL) throw("ListNode_getNodeAt: ListNode = NULL\n");
        ListNode *curr = self;
        int i = 0;
        while(curr != NULL && i != index) {
                curr = curr->next;
                i++;
        }
        if(i != index) throw("Невирный индекс\n");
        return curr;
}

// DONE
int ListNode_getLength(ListNode *self){
        if(self == NULL) return 0;
        int length = 1;
        ListNode *curr = self;
        while(curr->next != NULL) {
                length++;
                curr = curr->next;
        }
        return length;
}
