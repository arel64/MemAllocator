//
// Created by arels on 6/1/22.
//

#include <stdlib.h>
#include "allocator.h"
#define MAX_MEMORY = 500;
#define BAD_ALLOCATE 0xffffffffffffffff

void malloc_init(){

    //Init allocation and free linked lists

    initList(&alocList);
    initList(&freeList);

    //Establish Memory Baselines
    lowAddress = sbrk(500);
    maxAddress = sbrk(0);
}
void* malloc(unsigned long size){

    ListNode* iter = freeList.head;

    int status = inListMem(size,iter);
    unsigned long totalSize;
    ListNode* element;
    if(status == 1){
        /*
            Memory can be used from current size sbrk and iter points to the start of address
            able to fit size + sizeof(ListNode)
         */
        ListNode* temp;
        totalSize = size  + sizeof(ListNode);

        //We make sure free space is now less by totalSize as we will insert new header and element
        element = iter->key - sizeof(ListNode);
        element->length -= totalSize;


        //This now points to the first free byte after the freeElement scope
        temp = element + element->length ;
        temp->length = totalSize;
        temp->key = temp + sizeof(ListNode);

        //TODO if node is of 0 length remove it

        /*
            //Remove from free list
            deleteList(&freeList,aloc);
        */

        //Add node into allocation list
        insertList(&alocList,temp);

        return temp->key;
    }
    //No gap big enough found


    //This is the required additional memory to be allocated
    totalSize = size  + sizeof(ListNode);
    void* start = sbrk(totalSize);

    // void* start = sbrk(totalSize);
    if(start == BAD_ALLOCATE){
        return (void*)-1; //BAD!
    }
    element = start;
    element->length = totalSize;
    element->key = start + sizeof (ListNode);

    //Add node into allocation list
    insertList(&alocList,element);

    //This is now a pointer to size length allocated memory
    return element->key;

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

//TODO CHANGE TO MOST LEFT POINTER
int inListMem(unsigned long size,ListNode* iter){
   iter = freeList.head;
   //Free list is empty, oby no space
   if(iter == NULL){
       iter = NULL;
       return 0;
   }
   size_t totalSize = size + sizeof(ListNode);
   ListNode* minValNode = NULL;
   ListNode* prevNode = NULL;

   while(iter != NULL){
       if(iter->length >= totalSize &&(minValNode==NULL || iter->length < minValNode->length)){
           //This node is the smallest node to fit total size so far.
           minValNode = iter;
       }
       prevNode = iter;
       iter = iter->next;
   }
   //The function sets iter to the value of first free node, or end of list otherwise
   iter = prevNode;

   if(minValNode == NULL){
       return 0; //No fitting node found
   }
   //A fitting node was found , return it
   iter = minValNode;
   return 1;

}
