
#include "Mem/allocator.h"

void setArray(char* arr,unsigned length,char value);
int main() {
    malloc_init();

    unsigned array_size = 50;
    char* arr = malloc(sizeof(char)*array_size);
    setArray(arr,array_size,'a');
    char* arr2 = malloc(sizeof(char)*array_size);
    setArray(arr2,array_size,'b');
    char* arr3 = malloc(sizeof(char)*array_size);
    setArray(arr3,array_size,'c');

    free(arr);
    free(arr3);
    free(arr2);

    arr=NULL;
    arr2=NULL;
    arr3=NULL;

    arr=NULL;
    arr2=NULL;
    arr3=NULL;
    int count = 0;
    while(count < 2000){

        LOG("RUnning...",NOTE)
        usleep(10);
        count+=10;
    }
    char* arrA = malloc(sizeof(char)*array_size);
    setArray(arrA,array_size,'a');
    char* arrA2 = malloc(sizeof(char)*array_size);
    setArray(arrA2,array_size,'b');
    char* arrA3 = malloc(sizeof(char)*array_size);
    setArray(arrA3,array_size,'c');

    free(arrA);
    free(arrA2);
    free(arrA3);
    while(1){

        LOG("RUnning 2...",NOTE)
        usleep(10);
        count+=10;
    }
/*



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
void setArray(char* arr,unsigned length,char value){
    for (int i = 0; i < length ; ++i) {
        arr[i] = value;
        if(i==length -1)
            arr[i] = '\0';
    }
}