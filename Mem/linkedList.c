//
// Created by arels on 6/1/22.
//

#include "linkedList.h"

List alocList;
List freeList;

void initList(List* q){
    q->head = NULL;
}

ListNode* listSearch(List* l,void* key){
    ListNode* iter = l->head;
    while(iter != NULL){
        if(iter->key == key){
            return iter;
        }
        iter = iter->next;
    }
    return NULL;
}

void deleteList(List* l,ListNode* node){
    if(node->prev!=NULL){
        (node->prev)->next = node->next;
    }else{
        l->head = node->next;
    }
    if(node->next != NULL){
        (node->next)->prev = node->prev;
    }
}
void insertList(List* l,ListNode* node){
    node->next = l->head;
    if(l->head != NULL){
        l->head->prev = node;
    }
    l->head = node;
    node->prev = NULL;

}
