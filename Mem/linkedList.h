//
// Created by arels on 6/1/22.
//

#ifndef MEMALLOCATOR_LINKEDLIST_H
#define MEMALLOCATOR_LINKEDLIST_H

#include "globaldef.h"
#include <stddef.h>

typedef struct listNode
{
	unsigned long length;
	struct listNode *next;
	struct listNode *prev;
} ListNode;

typedef struct
{
	ListNode *head;
} List;

void initList(List *);
void insertList(List *, ListNode *);
void deleteNodeList(List *, ListNode *);
ListNode *searchList(List *, void *key);

#endif//MEMALLOCATOR_LINKEDLIST_H
