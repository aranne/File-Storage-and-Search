#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int input[buffer_size];
int output[buffer_size];
int output_size;

int load_buffer(int* buffer, int size, FILE* fp) {
    int read_size = fread(buffer, sizeof(int), size, fp);
    return read_size;
}

void write_buffer(int* buffer, int size, char* filename) {
    FILE* fp = fopen(filename, "wb");
    fwrite(buffer, size, sizeof(int), fp);
    fclose(fp);
}

void print_buffer(int* buffer) {
    int i;
    for (i = 0; i < buffer_size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

void sort_buffer(int* buffer, int sort_size) {
    qsort(buffer, sort_size, sizeof(int), compare);
}

