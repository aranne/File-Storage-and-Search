#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

const int INIT_SIZE = 8;
const int REFACTOR = 2;

void array_resize(Array *a, int new_size);

Array array_create(int size) {
    Array a;
    if (size == 0) {
        a.size = INIT_SIZE;
    } else {
        a.size = size;
    }
    a.num = 0;
    a.array = (index_S*) malloc(sizeof(index_S) * a.size);
    int i;
    for (i = 0; i < a.size; ++i) {
        index_S index = {-1, -1};
        a.array[i] = index;
    }
    return a;
}

void array_free(Array* a) {
    free(a->array);
    a->array = NULL;
    a->size = 0;
    a->num = 0;
}

int array_size(const Array* a) {
    return a->size;
}

int array_num(const Array* a) {
    return a->num;
}

index_S* array_at(const Array* a, int i) {
    return &(a->array[i]);
}

index_S array_get(const Array* a, int i) {
    return a->array[i];
}

void array_set(Array* a, int i, index_S index) {
    a->array[i] = index;
}

void array_add(Array* a, int i, index_S index) {
    if (a->num == a->size) {
        array_resize(a, a->size * REFACTOR);
    }
    int k;
    for (k = a->num - 1; k >= i; k--) {
        a->array[k + 1] = a->array[k];
    }
    a->array[i] = index;
    a->num++;
}

index_S array_delete(Array* a, int i) {
    int k;
    index_S index = a->array[i];
    for (k = i; k < a->num - 1; k++) {
        a->array[k] = a->array[k + 1];
    }
    a->num--;
    return index;
}

void array_resize(Array *a, int new_size) {
    index_S *p = (index_S*) malloc(sizeof(index_S) * new_size);
    int num = a->num;
    memcpy(p, a->array, sizeof(index_S) * a->size);
    int i;
    for (i = a->size; i < new_size; ++i) {
        index_S index = {-1, -1};
        p[i] = index;
    }
    array_free(a);
    a->array = p;
    a->size = new_size;
    a->num = num;
}

void array_print(const Array* a) {
    if (a->num == 0) {
        printf("[]\n");
    } else {
        printf("[");
        int i;
        for (i = 0; i < a->num - 1; ++i) {
            printf("%d,", a->array[i].key);
        }
        printf("%d]\n", a->array[i].key);
    }
}