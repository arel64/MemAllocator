//
// Created by arels on 6/1/22.
//

#ifndef MEMALLOCATOR_LINKEDLIST_H
#define MEMALLOCATOR_LINKEDLIST_H

#include <stddef.h>

typedef struct listNode{
    void* key;
    long length;
    struct listNode* next;
    struct listNode* prev;
}ListNode;

typedef struct{
    ListNode* head;
}List;

void initList(List*);
void insertList(List*,ListNode*);
void deleteList(List*,ListNode*);
ListNode* listSearch(List*,void* key);

#endif //MEMALLOCATOR_LINKEDLIST_H
