//
// Created by arels on 6/4/22.
//

#include "defragger.h"
#include <stdio.h>
#include <stdlib.h>

pthread_t defragThread;
pthread_mutex_t allocMutex;
void initDefragger(List* freeList){
    if(pthread_create(&defragThread,NULL,  defragFreeList,freeList)){
        log("Unable to create defragThread Mutex.",CRITICAL)
        exit(1);
    }
    if(pthread_mutex_init(&allocMutex,NULL)){
        log("Unable to create defragThread Mutex.",CRITICAL);
        exit(1);
    }

}
void defragFreeList(List* freeList){

}