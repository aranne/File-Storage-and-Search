#ifndef mergesort_h
#define mergesort_h

#include <stdio.h>

extern FILE* input_fp;
extern FILE* output_fp;

typedef struct {
    int value;
    int num;
} node;

typedef struct {
    int size;
    int index;
    int* start;
} run;

#define replace_heap_size 750
#define replace_input_size 250

void basic_mergesort(const char* input_f, const char* output_f);
void multistep_mergesort(const char* input_f, const char* output_f);
void replacement_mergesort(const char* input_f, const char* output_f);

#endif