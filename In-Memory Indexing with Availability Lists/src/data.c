#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "db.h"
#include "primindex.h"
#include "holelist.h"


ArrayList holelist;
Array primindex;
FILE* dbfp;
const char* filename;
const char* indexname;
const char* listname;

FILE* load_data() {
    FILE* fp = fopen(filename, "r+b");
    if (fp == NULL) {
        fp = fopen(filename, "w+b");
        FILE* tmp;
        tmp = fopen(listname, "w+b");  // clear list file
        fclose(tmp);
        tmp = fopen(indexname, "w+b"); // clear index file
        fclose(tmp);
    }
    return fp;
}

void write_data(FILE* fp) {
    fclose(fp);
}

void add_record(const char* keystr, const char* record) {
    int key = atoi(keystr);
    /* Bi​nary search the index for an entry with record's key */
    long flag = findindex(&primindex, key);
    if (flag != -1) {           // if find entry in index
        printf("Record with SID=%d exists\n", key);
        return;
    }
    size_t len = strlen(record) - 1;              // remove ending '\0' 
    size_t size = sizeof(int) + len;
    /* Search the avail​abil​ity list for a hole */
    int hole_index = find_hole(&holelist, size);
    long offset;
    if (hole_index == -1) {
        fseek(dbfp, 0, SEEK_END);
        offset = ftell(dbfp);
        write_record(offset, (int) len, record);
    } else {
        avail_S* array = holelist.array;
        size_t hole_size = array[hole_index].size;
        offset = array[hole_index].offset;
        long off = write_record(offset, (int) len, record);
        delete_hole(&holelist, hole_index);
        if (hole_size > size) {
            avail_S hole = {hole_size - size, off};
            add_hole(&holelist, hole);
        }
    }
    /* Add new entry to index */
    index_S index = {key, offset};
    addindex(&primindex, index);
}

long write_record(long offset, int len, const char* record) {
    fseek(dbfp, offset, SEEK_SET);
    fwrite(&len, sizeof(int), 1, dbfp);
    fwrite(record, len, 1, dbfp);
    return ftell(dbfp);
}

char* read_record(long offset) {
    fseek(dbfp, offset, SEEK_SET);
    int size;
    char* record;
    fread(&size, sizeof(int), 1, dbfp);
    record = (char*) malloc((size_t) size + 1);
    fread(record, size, 1, dbfp);
    record[size] = '\0';                         // add ending '\0'
    return record;
}

int find_record(const char* keystr) {
    int key = atoi(keystr);
    long offset = findindex(&primindex, key);
    if (offset == -1) {
        printf("No record with SID=%d exists\n", key);
        return 0;
    }
    char* record = read_record(offset);
    printf("%s\n", record);
    free(record);
    return 1;
}

int delete_record(const char* keystr) {
    int key = atoi(keystr);
    int* pair = binarySearch(&primindex, key);
    if (!pair[0]) {
        printf("No record with SID=%d exists\n", key);
        return 0;
    }
    int index = pair[1];
    int offset = primindex.array[index].offset;
    int size;
    fseek(dbfp, offset, SEEK_SET);
    fread(&size, sizeof(int), 1, dbfp);
    size_t hole_size = sizeof(int) + (size_t) size;
    avail_S hole = {hole_size, offset};
    add_hole(&holelist, hole);
    deleteindex(&primindex, index);
    return 1;
}


