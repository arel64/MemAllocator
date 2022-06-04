
#include "Mem/allocator.h"

void setArray(char* arr,int length,char value);
int main() {
    malloc_init();

    printf("banana %d",4);
    unsigned array_size = 50;
    char* arr = malloc(sizeof(char)*array_size);
    setArray(arr,array_size,'a');
    free(arr);
    arr=NULL;
    char* arr2 = malloc(sizeof(char)*array_size);
    setArray(arr2,array_size,'b');


/*

    char* arr2 = malloc(sizeof(char)*array_size);
    setArray(arr2,array_size,'b');


    char* arr3 = malloc(sizeof(char)*array_size);
    setArray(arr3,array_size,'c');


    free(arr2);
    arr2=NULL;
    int halfsize =(array_size/2);
    char* small1 = malloc(sizeof(char)*halfsize);
    setArray(small1,halfsize,'d');

    char* small2 = malloc(sizeof(char)* halfsize);
    setArray(small2,halfsize,'e');

    free(arr);
    free(small1);
    free(small2);
    free(arr3);
    arr=small1=small2=arr3=NULL;
*/

    return 0;
}
void setArray(char* arr,int length,char value){
    for (int i = 0; i < length ; ++i) {
        arr[i] = value;
        if(i==length -1)
            arr[i] = '\0';
    }
}