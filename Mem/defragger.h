//
// Created by arels on 6/4/22.
//

#ifndef MEMALLOCATOR_DEFRAGGER_H
#define MEMALLOCATOR_DEFRAGGER_H

#include "linkedList.h"
#include "pthread.h"
extern pthread_t defragThread;
extern pthread_mutex_t allocMutex;
void initDefragger(List*);
void defragFreeList(List*);



#endif //MEMALLOCATOR_DEFRAGGER_H
