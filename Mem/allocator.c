/**
 * @author Arel Sharon
 * @since 01/06/2022
 * @brief Attempt at malloc reimplementation
 *
 */

#include <stdlib.h>
#include "allocator.h"

int isInit = 0;

/**
 * Will establish a memory baseline and end in order to not interfere with system allocations
 * **Must** Be called at first line of main
 *
 */
void malloc_init(){
    //Init allocation and free linked lists

    initList(&alocList);
    initList(&freeList);

    //Mark all space as free
    isInit = 1;


    initDefragger(&freeList);
}
void* malloc(unsigned long size){
    if(isInit != 1){
        malloc_init();
    }
    //Find a free memory block of appropriate size

    ListNode* freeElement;
    int status = searchFreeMemoryBlock(size,&freeElement);


    if(status) {
        status = increaseAvailableMemory(size,&freeElement);
        if(status){
            return (void*)BAD_ALLOCATE;
        }
    }

    /*
        Memory can be used from current size sbrk and iter points to the start of address
        able to fit size + 2 * sizeof(ListNode)
        or size + sizeof(ListNode) in the case of an exact fit.
     */

    unsigned long totalSize = size  + sizeof(ListNode);
    ListNode* allocationNode;


    //We make sure free space is now less by totalSize as we will insert new header and element

    freeElement->length -= totalSize;


    //If we allocated all the node size, remove it.

    if(freeElement->length == 0){
        deleteNodeList(&freeList, freeElement);
    }


    //temp now points to adress where the alloc header is to be placed.

    allocationNode = (void*) (getKey(freeElement) - sizeof(ListNode) + freeElement->length);
    allocationNode->length = totalSize;


    //Add node into allocation list
    insertList(&alocList,allocationNode);


    //Address just after header to write into
    return (void*)getKey(allocationNode);
}
void free(void* addr){


    //free NULL is safe
    if(addr == NULL){
        return;
    }

    //Remember we offset the key by sizeof ListNode
    void* key = addr;

    //Find the allocation node in aloclist and get a pointer to it
    ListNode* allocated = searchList(&alocList,key);
    if(allocated!=NULL){

        //Delete from the aloc list
        deleteNodeList(&alocList, allocated);

        //Insert into the free list as this block is now free!
        insertList(&freeList,allocated);
    }

    pthread_cond_signal(&freedMemoryCond);

}

int searchFreeMemoryBlock(unsigned long size,ListNode ** iterPtr){

    ListNode* iter = freeList.head;
   //Free list is empty, oby no space
   if(iter == NULL){
       return 1;
   }

   //Note that the total size is 2 List nodes as there is need of length for both the header for the FreeList and AlocList.
   unsigned long totalSize          = size + 2 * sizeof(ListNode);
   unsigned long totalSizeExactFit  = size + sizeof(ListNode);
   ListNode* minValNode             = NULL;


   //Iterate over linked list while searching for free block
   while(iter != NULL){
       if(iter->length >= totalSize &&
            (minValNode==NULL || iter->length < minValNode->length))
       {
           //This node is the smallest node to fit total size so far.
           minValNode = iter;
       }
       if(totalSizeExactFit == iter->length)
       {
           //This is an exact fit, no need to test other blocks
           *iterPtr = iter;
           return 0;
       }
       iter = iter->next;
   }

   if(!minValNode){
       return 1;
   }
    //A memory block was found , return it
    *iterPtr = minValNode;
   return 0;
}
int increaseAvailableMemory(unsigned long size,ListNode** freeElement){
    int amountOfBuffers = ceil((double)(size+sizeof(ListNode))/BUFFER_SIZE);
    unsigned long totalSize = amountOfBuffers * BUFFER_SIZE;

    void* res = sbrk(totalSize);
    if(!res){
        //No memory to be allocated(Possibly other problem)
        return 1;
    }

    *freeElement = res;
    (*freeElement)->length = totalSize;
    insertList(&freeList,*freeElement);
    return 0;
}
