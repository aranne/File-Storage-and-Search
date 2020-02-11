#include <stdio.h>
#include "primindex.h"
#include "array.h"
#include "db.h"

const char* indexname;
int* binarySearch(Array* a, int key);

Array loadindex() {
    Array a = array_create(0);
    FILE* fp = fopen(indexname, "r+b");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        size_t num = ftell(fp) / sizeof(index_S);
        a = array_create((int) num);
        fseek(fp, 0, SEEK_SET);
        size_t read_num = fread(a.array, sizeof(index_S), num, fp);
        if (num != read_num) {
            array_free(&a);
            printf("Read Index Error\n");
        }
        a.num = (int) num;
        a.size = (int) num;
        fclose(fp);
    }
    return a;
}

void writeindex(Array* index) {
    FILE* fp = fopen(indexname, "w+b");
    fseek(fp, 0, SEEK_SET);
    fwrite(index->array, sizeof(index_S), index->num, fp);
    freeindex(index);
    fclose(fp);
}

void freeindex(Array* index) {
    array_free(index);
}

void addindex(Array* index, index_S idx) {
    int* pair = binarySearch(index, idx.key);
    if (pair[0]) {
        printf("Record with SID=%d exists\n", idx.key);
    } else {
        array_add(index, pair[1], idx);
    }
}

long findindex(Array* index, int key) {
    int* pair = binarySearch(index, key);
    if (pair[0]) {
        return index->array[pair[1]].offset;
    } else {
        printf("No record with SID=%d exists\n", key);
        return -1;
    }
}

/* return -> [True, value] */
int* binarySearch(Array* a, int key) {
    int pair[2] = {0, -1};
    int* res = pair;
    int left = 0;
    int right = a->num;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a->array[mid].key == key) {
            pair[0] = 1;
            pair[1] = mid;
            return res;
        } else if (a->array[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    pair[1] = right;
    return res;
}

void printindex(Array* index) {
    if (index->num == 0) return;
    printf("Index:\n");
    int i;
    for (i = 0; i < index->num; i++) {
        printf("key=%d: offset=%ld\n", index->array[i].key, index->array[i].offset);
    }
}