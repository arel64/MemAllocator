//
// Created by arels on 6/1/22.
//

#include <stdlib.h>
#include "allocator.h"
#define BAD_ALLOCATE -1
void malloc_init(){

    ListNode *start = sbrk(sizeof(List));

    if(*(int*)start ==BAD_ALLOCATE){
        printf("No memory to init");
        exit(1);
    }
    //Init allocation and free linked lists

    initList(&alocList);
    initList(&freeList);


    //Keep start of usable memory as head of list
    start->key  = sbrk(0);
    start->next =NULL;
    start->prev =NULL;
    alocList.head = start;
    alocList.size = 0;

}
void* malloc(size_t size){

    ListNode* iter = alocList.head;

    int status = inListMem(size,iter);
    if(status == 1){
        /*
            Memory can be used from current size sbrk and iter points to the start of address
            able to fit size +
         */
        ListNode* sep = iter->key;
        //Create new allocation node, with appropriate size
        sep->key = iter->key + sizeof(ListNode);
        sep->length = size;


        //TODO if node is of 0 length remove it
        //Free now points totalSize after initial location and has totalSize less free space
        size_t totalSize = sep->length  + sizeof(ListNode);
        iter->key = iter->key + totalSize;
        iter->length = iter->length - totalSize;

        //Add node into list
        insertList(&alocList,sep);

        return sep->key;
    }
    //No gap big enough found


    void* start = sbrk(0);

    //This is the required additional memory to be allocated
    long diffReq = (start - iter->key);

    if(*(int*)sbrk(diffReq) == BAD_ALLOCATE){
        return (void*)-1; //BAD!
    }


    //This is now a pointer to size length allocated memory
    return start;

}
void free(void* addr){
    //free NULL is safe
    if(addr == NULL){
        return;
    }

    //Remember we offset the key by sizeof ListNode
    void* key = addr - sizeof (ListNode);

    //Find the allocation node in aloclist and get a pointer to it
    ListNode* allocated = listSearch(&alocList,key);
    if(allocated!=NULL){

        //Delete from the aloc list
        deleteList(&alocList,allocated);

        //Insert into the free list as this block is now free!
        insertList(&freeList,allocated);

    }
}


int inListMem(size_t size,ListNode* iter){
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
ListNode* listSearch(List* l,void* key){
    ListNode* iter = l->head;
    while(iter != NULL){
        if(iter->key == key){
            return iter;
        }
        iter = iter->next;
    }
}
