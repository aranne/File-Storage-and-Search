#ifndef db_h
#define db_h

#include <stdio.h>
#include "primindex.h"
#include "holelist.h"

extern const char* mode;
extern const char* filename;
extern const char* indexname;
extern const char* listname;
extern int running;

extern ArrayList holelist;
extern Array primindex;
extern FILE* dbfp;

#endif