#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "load.h"

int main(int argc, const char * argv[]) {
    printf("Hello, world!\n");
    const char* key = argv[1];
    Array a = load(key);
    int size = a.size;
    int* p = a.array;
    printf("%d\n", size);
    while (size--) {
        printf("%d\n", *p++);
    }
    // free malloc address
    free(a.array);
    a.array = NULL;
    a.size = 0;
    return 0;
}