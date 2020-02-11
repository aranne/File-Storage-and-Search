#ifndef array_h
#define array_h

#include "index.h"

typedef struct {
    index_S* array;
    int size;
    int num;
} Array;

Array array_create(int size);
void array_free(Array* a);
int array_size(const Array* a);
int array_num(const Array* a);
index_S* array_at(const Array* a, int i);
index_S array_get(const Array* a, int i);
void array_set(Array* a, int i, index_S index);
void array_add(Array* a, int i, index_S index);
index_S array_delete(Array* a, int i);
void array_print(const Array* a);

#endif