#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"

Array load(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    int* buffer = NULL;
    Array a = {NULL, 0};
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp) / sizeof(int);
        buffer = (int*) malloc(size * sizeof(int));
        fseek(fp, 0, SEEK_SET);
        int read_size = fread(buffer, sizeof(int), size, fp);
        if (size != read_size) {
            free(buffer);
            printf("Read data error\n");
        }
        a.array = buffer;
        a.size = size;
        fclose(fp);
    } else {
        printf("Open file failed\n");
    }
    return a;
}