#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

# define LLTYPE      void *
# define LLTYPE_SIZE sizeof(LLTYPE)

struct LinkedList;

struct LinkedList *createLinkedList();
void  deleteLinkedList(struct LinkedList *l);

int   isEmptyLinkedList(struct LinkedList *l);
void  pushLinkedList(struct LinkedList *l, LLTYPE val);
LLTYPE  topLinkedList(struct LinkedList *l);
void  popLinkedList(struct LinkedList *l);

#endif

