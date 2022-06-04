//
// Created by arels on 6/1/22.
//

#ifndef MEMALLOCATOR_ALLOCATOR_H
#define MEMALLOCATOR_ALLOCATOR_H



#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "defragger.h"

#define BAD_ALLOCATE (-1)
#define MAX_MEMORY 10000


extern List alocList;
extern List freeList;
extern void* lowAddress;
extern void* maxAddress;

void malloc_init();

void* malloc(size_t size);
void free(void*);

int searchFreeMemoryBlock(unsigned long,ListNode **);
#endif //MEMALLOCATOR_ALLOCATOR_H
