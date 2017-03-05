#ifndef LISTNODE_H
#define LISTNODE_H

typedef struct ListNode ListNode;

ListNode *ListNode_new(void *data);
void ListNode_free(ListNode **self, void (*dataFree)(void *));
void ListNode_freeAll(ListNode **self, void (*dataFree)(void *));
void *ListNode_getData(ListNode *self);
ListNode *ListNode_getNext(ListNode *self);
ListNode *ListNode_addAfter(ListNode *self, ListNode *addNode);
ListNode *ListNode_addBefore(ListNode *self, ListNode *addNode);
ListNode *ListNode_remove(ListNode *self, int index);
ListNode *ListNode_getNodeAt(ListNode *self, int index);
int ListNode_getLength(ListNode *self);

#endif
