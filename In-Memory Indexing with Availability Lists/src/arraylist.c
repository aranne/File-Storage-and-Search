#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

const int INITSIZE = 128;
const int FACTOR = 2;

void list_resize(ArrayList* a, int new_size);

ArrayList list_create(int size) {
    ArrayList a;
    if (size == 0) {
        a.size = INITSIZE;
    } else {
        a.size = size;
    }
    a.num = 0;
    a.array = (avail_S*) malloc(sizeof(avail_S) * a.size);
    int i;
    for (i = 0; i < a.size; ++i) {
        avail_S hole = {-1, -1};
        a.array[i] = hole;
    }
    return a;
}

void list_free(ArrayList* a) {
    free(a->array);
    a->array = NULL;
    a->size = 0;
    a->num = 0;
}

int list_size(const ArrayList* a) {
    return a->size;
}

int list_num(const ArrayList* a) {
    return a->num;
}

avail_S* list_at(const ArrayList* a, int i) {
    return &(a->array[i]);
}

avail_S list_get(const ArrayList* a, int i) {
    return a->array[i];
}

void list_set(ArrayList* a, int i, avail_S hole) {
    a->array[i] = hole;
}

void list_add(ArrayList* a, int i, avail_S hole) {
    if (a->num == a->size) {
        list_resize(a, a->size * FACTOR);
    }
    int k;
    for (k = a->num - 1; k >= i; k--) {
        a->array[k + 1] = a->array[k];
    }
    a->array[i] = hole;
    a->num++;
}

avail_S list_delete(ArrayList* a, int i) {
    int k;
    avail_S hole = a->array[i];
    for (k = i; k < a->num - 1; k++) {
        a->array[k] = a->array[k + 1];
    }
    a->num--;
    return hole;
}

void list_resize(ArrayList *a, int new_size) {
    avail_S *p = (avail_S*) malloc(sizeof(avail_S) * new_size);
    int num = a->num;
    memcpy(p, a->array, sizeof(avail_S) * a->size);
    int i;
    for (i = a->size; i < new_size; ++i) {
        avail_S hole = {-1, -1};
        p[i] = hole;
    }
    list_free(a);
    a->array = p;
    a->size = new_size;
    a->num = num;
}

void list_print(const ArrayList* a) {
    if (a->num == 0) {
        printf("[]\n");
    } else {
        printf("[");
        int i;
        for (i = 0; i < a->num - 1; ++i) {
            printf("%zu,", a->array[i].size);
        }
        printf("%zu]\n", a->array[i].size);
    }
}