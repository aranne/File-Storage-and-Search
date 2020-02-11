#include <stdio.h>
#include "primindex.h"
#include "array.h"
#include "db.h"

FILE* fp = NULL;
const char* indexname;

Array loadindex() {
    Array a = array_create(0);
    fp = fopen(indexname, "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int num = ftell(fp) / sizeof(index_S);
        a = array_create(num);
        fseek(fp, 0, SEEK_SET);
        int read_num = fread(a.array, sizeof(index_S), num, fp);
        if (num != read_num) {
            array_free(&a);
            printf("Read Index Error\n");
        }
        a.num = num;
        a.size = num;
        fclose(fp);
    }
    return a;
}

void writeindex(Array* index) {
    fp = fopen(indexname, "wb");
    fwrite(index->array, sizeof(index_S), index->num, fp);
    freeindex(index);
    fclose(fp);
}

void freeindex(Array* index) {
    array_free(index);
}