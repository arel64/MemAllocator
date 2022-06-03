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



    unsigned long totalSize;
    ListNode* freeElement;
    if(status != 1) {
        //No data gap found, no space at this time
        return (void*)BAD_ALLOCATE;
    }
    /*
        Memory can be used from current size sbrk and iter points to the start of address
        able to fit size + sizeof(ListNode)
     */
    ListNode* temp;
    totalSize = size  + sizeof(ListNode);

    //We make sure free space is now less by totalSize as we will insert new header and element
    freeElement = iter->key - sizeof(ListNode);
    freeElement->length -= totalSize;


    //This now points to the first free byte after the freeElement scope
    temp = freeElement->key - sizeof(ListNode) + freeElement->length ;
    temp->length = totalSize;
    temp->key = temp + 1; //One iteration means sizeof listnode

    //TODO if node is of 0 length remove it
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
       iter = NULL;
       return 0;
   }
   //Note that the total size is 2 Listnodes as there is need of length for both the header for the FreeList and AlocList.
   size_t totalSize = size + 2 * sizeof(ListNode);
   ListNode* minValNode = NULL;
   ListNode* prevNode = NULL;

   while(iter != NULL){
       if(iter->length >= totalSize && (minValNode==NULL || iter->length < minValNode->length)){
           //This node is the smallest node to fit total size so far.
           minValNode = iter;
       }
       prevNode = iter;
       iter = iter->next;
   }
   //The function sets iter to the value of first free node, or end of list otherwise
    *iterPtr = prevNode;

   if(minValNode == NULL){
       return 0; //No fitting node found
   }
   //A fitting node was found , return it
   *iterPtr = minValNode;
   return 1;

}
