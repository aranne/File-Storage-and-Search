#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Array.h"

// typedef struct {
//     int* array;
//     int size;
// } Array;


Array array_create(int size) {
    Array a;
    if (size == 0) {
        a.size = 0;
        a.array = NULL;
        return a;
    }
    a.size = size;
    a.array = (int*) malloc(sizeof(int) * a.size);
    int i;
    for (i = 0; i < a.size; ++i) {
        a.array[i] = 0;
    }
    return a;
}

void array_free(Array* a) {
    free(a->array);
    a->array = NULL;
    a->size = 0;
}