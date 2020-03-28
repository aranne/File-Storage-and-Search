#include <stdio.h>
#include <string.h>
#include "mergesort.h"
#include "buffer.h"

FILE* input_fp = NULL;
FILE* output_fp = NULL;

void update_id(char * id);

void basic_mergesort(const char* input_f, const char* output_f) {
    FILE* input_fp = fopen(input_f, "rb");
    if (input_fp == NULL) {
        printf("Open file failed\n");
        return;
    }
    init_buffer();
    int load_size;
    char id[4] = "000";
    char filename[20];
    while ( (load_size = load_buffer(buffer_size, input_fp)) != 0) {
        sort_buffer(input, load_size);
        strcpy(filename, input_f);
        strcat(filename, ".");
        strcat(filename, id);
        write_buffer(input, load_size, filename);
        update_id(id);
    }
    fclose(input_fp);
}

void update_id(char * id) {
    if (id[2] == '9') {
        id[2] = '0';
        if (id[1] == '9') {
            id[1] = '0';
            if (id[0] == '9') {
                id[0] = '0';
            } else {
                id[0]++;
            }
        } else {
            id[1]++;
        }
    } else {
        id[2]++;
    }
}