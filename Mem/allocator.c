//
// Created by arels on 6/1/22.
//

#include <stdlib.h>
#include "allocator.h"
#define MAX_MEMORY 500
#define BAD_ALLOCATE -1


void* lowAddress;
void* maxAddress;

void malloc_init(){

    //Init allocation and free linked lists

    initList(&alocList);
    initList(&freeList);

    //Establish Memory Baselines
    lowAddress = sbrk(MAX_MEMORY);
    maxAddress = sbrk(0);

    //Mark all space as free
    ListNode* freeBaseLine = lowAddress;
    freeBaseLine->key = lowAddress + sizeof(ListNode);
    freeBaseLine->length = MAX_MEMORY;

    insertList(&freeList,freeBaseLine);

}
void* malloc(unsigned long size){

    ListNode* iter;
    int status = inListMem(size,&iter);



    if(status != 1) {
        //No data gap found, no space at this time
        return (void*)BAD_ALLOCATE;
    }
    /*
        Memory can be used from current size sbrk and iter points to the start of address
        able to fit size + 2*sizeof(ListNode)
     */
    unsigned long totalSize;
    ListNode* freeElement;
    ListNode* temp;
    totalSize = size  + sizeof(ListNode);

    //We make sure free space is now less by totalSize as we will insert new header and element

    freeElement = iter->key - sizeof(ListNode);
    freeElement->length -= totalSize;

    //If we allocated all the node size, remove it.

    if(freeElement->length == 0){
        deleteList(&freeList,freeElement);
    }




    //This now points to the first free byte after the freeElement scope
    temp = freeElement->key - sizeof(ListNode) + freeElement->length ;
    temp->length = totalSize;
    temp->key = temp + 1; //One iteration means sizeof listnode


    //Add node into allocation list
    insertList(&alocList,temp);

    return temp->key;
}
void free(void* addr){
    //free NULL is safe
    if(addr == NULL){
        return;
    }

    //Remember we offset the key by sizeof ListNode
    void* key = addr;

    //Find the allocation node in aloclist and get a pointer to it
    ListNode* allocated = listSearch(&alocList,key);
    if(allocated!=NULL){

        //Delete from the aloc list
        deleteList(&alocList,allocated);

        //Insert into the free list as this block is now free!
        insertList(&freeList,allocated);

    }
}

int inListMem(unsigned long size,ListNode ** iterPtr){

    ListNode* iter = freeList.head;
   //Free list is empty, oby no space
   if(iter == NULL){
       return 0;
   }

   //Note that the total size is 2 Listnodes as there is need of length for both the header for the FreeList and AlocList.
   size_t totalSize = size + 2 * sizeof(ListNode);
   size_t totalSizeExactFit = size + sizeof(ListNode);
   ListNode* minValNode = NULL;
   ListNode* prevNode = NULL;

   while(iter != NULL){
       if(iter->length >= totalSize && (minValNode==NULL || iter->length < minValNode->length)){
           //This node is the smallest node to fit total size so far.
           minValNode = iter;
       }
       if(totalSizeExactFit == iter->length){
           //This is an exact fit, no need to test other blocks
           *iterPtr = iter;
           return 1;
       }
       prevNode = iter;
       iter = iter->next;
   }

   //A fitting node was found , return it
   *iterPtr = minValNode;
   return 1;

}
