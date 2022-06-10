//
// Created by arels on 6/4/22.
//defragKill

#ifndef MEMALLOCATOR_DEFRAGGER_H
#define MEMALLOCATOR_DEFRAGGER_H

#include "linkedList.h"
#include "pthread.h"
void initDefragger(List*);
void defragFreeList(List*);
static inline void mergeInto(List*,ListNode*, ListNode*);


void defragKill(); //TESTING

extern pthread_cond_t freedMemoryCond;
#endif //MEMALLOCATOR_DEFRAGGER_H
