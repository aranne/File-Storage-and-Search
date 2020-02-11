#ifndef primindex_h
#define primindex_h

#include "index.h"
#include "array.h"

extern Array primindex;

Array loadindex(void);
void writeindex(Array* index);
void freeindex(Array* index);

#endif