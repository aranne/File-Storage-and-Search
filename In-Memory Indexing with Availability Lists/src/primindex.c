#include <stdio.h>
#include "primindex.h"
#include "db.h"

const char* indexname;

Array load_index() {
    Array a = array_create(0);
    FILE* fp = fopen(indexname, "r+b");
    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        size_t num = ftell(fp) / sizeof(index_S);
        if ((int) num == 0) {
            a = array_create(0);
        } else {
            a = array_create((int) num * 2);
        }
        fseek(fp, 0, SEEK_SET);
        size_t read_num = fread(a.array, sizeof(index_S), num, fp);
        if (num != read_num) {
            array_free(&a);
            printf("Read Index Error\n");
        }
        a.num = (int) num;
        fclose(fp);
    }  
    return a;
}

void write_index(Array* index) {
    FILE* fp = fopen(indexname, "w+b");
    fseek(fp, 0, SEEK_SET);
    fwrite(index->array, sizeof(index_S), index->num, fp);
    freeindex(index);
    fclose(fp);
}

void freeindex(Array* index) {
    array_free(index);
}

int addindex(Array* index, index_S idx) {
    int flag;
    int* pair = binarySearch(index, idx.key);
    if (pair[0]) {
        flag = 0;
    } else {
        array_add(index, pair[1], idx);
        flag = 1;
    }
    return flag;
}

long findindex(Array* index, int key) {
    int* pair = binarySearch(index, key);
    if (pair[0]) {
        return index->array[pair[1]].offset;
    } else {
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

index_S deleteindex(Array* index, int i) {
    return array_delete(index, i);
}

void printindex(Array* index) {
    printf("Index:\n");
    int i;
    for (i = 0; i < index->num; i++) {
        printf("key=%d: offset=%ld\n", index->array[i].key, index->array[i].offset);
    }
}