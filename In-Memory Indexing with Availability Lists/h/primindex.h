#ifndef primindex_h
#define primindex_h

#include "array.h"

extern Array primindex;

Array loadindex(void);
void writeindex(Array* index);
void freeindex(Array* index);
void addindex(Array* index, index_S idx);
long findindex(Array* index, int key);
void printindex(Array* index);

#endif