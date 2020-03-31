#ifndef heap_h
#define heap_h

#include "mergesort.h"

void heapfy(node* array, int size);
void sink(node* array, int i, int size);
void swap(node* array, int i, int j);
void heapfy_array(int* array, int size);
void sink_array(int* array, int i, int size);
void swap_array(int* array, int i, int j);


#endif