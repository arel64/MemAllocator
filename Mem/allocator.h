//
// Created by arels on 6/1/22.
//

#ifndef MEMALLOCATOR_ALLOCATOR_H
#define MEMALLOCATOR_ALLOCATOR_H


#include "defragger.h"
#include <math.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define BAD_ALLOCATE (-1)
#define BUFFER_SIZE (1024 + sizeof(ListNode))

extern List alocList;
extern List freeList;
extern void *lowAddress;
extern void *maxAddress;

void malloc_init();

void *malloc(size_t size);
void free(void *);

int increaseAvailableMemory(unsigned long, ListNode **);
int searchFreeMemoryBlock(unsigned long, ListNode **);


#endif//MEMALLOCATOR_ALLOCATOR_H
