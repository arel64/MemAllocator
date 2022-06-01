//
// Created by arels on 6/1/22.
//

#ifndef MEMALLOCATOR_ALLOCATOR_H
#define MEMALLOCATOR_ALLOCATOR_H



#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "linkedList.h"

extern List alocList;
extern List freeList;

void malloc_init();

void* malloc(size_t size);
void free(void* addr);

int inListMem(size_t,ListNode*);
#endif //MEMALLOCATOR_ALLOCATOR_H
