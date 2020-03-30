#ifndef heap_h
#define heap_h

#include "mergesort.h"

void heapfy(node* array, int size);
void sink(node* array, int i, int size);
void swap(node* array, int i, int j);


#endif