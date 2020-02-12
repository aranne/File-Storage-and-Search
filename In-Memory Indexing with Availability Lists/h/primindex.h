#ifndef primindex_h
#define primindex_h

#include "array.h"

Array load_index(void);
void write_index(Array* index);
void freeindex(Array* index);
int addindex(Array* index, index_S idx);
long findindex(Array* index, int key);
index_S deleteindex(Array* index, int i);
int* binarySearch(Array* a, int key);
void printindex(Array* index);

#endif