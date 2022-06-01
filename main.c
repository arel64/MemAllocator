#include <stdio.h>
#include "Mem/allocator.h"
int main() {

    malloc_init();




    printf("Hello, World!\n");
    char* arr;
    arr = malloc(sizeof(char)*4088);
    arr[4087] = 'c';
    free(&arr);
    return 0;
}
