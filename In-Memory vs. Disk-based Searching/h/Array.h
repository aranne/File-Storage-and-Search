#ifndef Array_h
#define Array_h

typedef struct {
    int* array;
    int size;
} Array;

Array array_create(int size);
void array_free(Array* a);

#endif


