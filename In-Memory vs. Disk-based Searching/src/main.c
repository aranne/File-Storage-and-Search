#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "load.h"

int main(int argc, const char * argv[]) {
    printf("Hello, world!\n");
    char* key = argv[1];
    Array a = load(key);
    int size = a.size;
    int* p = a.array;
    while (size--) {
        printf("%d\n", *p++);
    }
    a.size = 0;
    free(a.array);
    a.array = NULL;
    // free(buffer);
    return 0;
}