#include <stdio.h>
#include "Array.h"
#include "load.h"

Array load(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    Array a = {NULL, 0};
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp) / sizeof(int);
        a = array_create(size);
        fseek(fp, 0, SEEK_SET);
        int read_size = fread(a.array, sizeof(int), size, fp);
        if (size != read_size) {
            array_free(&a);
            printf("Read data error\n");
        }
        fclose(fp);
    } else {
        printf("Open file failed\n");
    }
    return a;
}