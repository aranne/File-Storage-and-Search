#ifndef hole_h
#define hole_h

#include <stdio.h>

typedef struct {
    size_t size;   /* Hole's size */
    long offset;   /* Hole's off​set in file */
} avail_S;

#endif