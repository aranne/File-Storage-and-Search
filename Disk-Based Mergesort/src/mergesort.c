#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"
#include "buffer.h"

FILE* input_fp = NULL;
FILE* output_fp = NULL;

void update_id(char * id);
int create_runs(const char* input_f);
void merge_runs(const char* input_f, int num);
void merge(FILE** fps, int** bps, int num);

void basic_mergesort(const char* input_f, const char* output_f) {
    input_fp = fopen(input_f, "rb");
    if (input_fp == NULL) {
        printf("Open file failed\n");
        return;
    }
    int runs = create_runs(input_f);
    // merge_runs(input_f, runs);
    fclose(input_fp);
}

int create_runs(const char* input_f) {
    int load_size;
    char id[4] = "000";
    char filename[30];
    int runs = 0;
    init_buffer();
    while ( (load_size = load_buffer(input, buffer_size, input_fp)) != 0) {
        sort_buffer(input, load_size);
        strcpy(filename, input_f);
        strcat(filename, ".");
        strcat(filename, id);
        write_buffer(input, load_size, filename);
        update_id(id);
        runs++;
    }
    return runs;
}

void merge_runs(const char* input_f, int num) {
    char id[4] = "000";
    char filename[30];
    int runs;
    FILE** fps = (FILE**) malloc(num * sizeof(FILE*));
    int** bps = (int**) malloc(num * sizeof(int*));   // block address
    int load_size = buffer_size / num;
    bps[0] = input;
    for (runs = 1; runs < num; runs++) {
        bps[runs] = bps[runs - 1] + load_size;
    }
    init_buffer();
    for (runs = 0; runs < num; runs++) {
        strcpy(filename, input_f);
        strcat(filename, ".");
        strcat(filename, id);
        update_id(id);
        fps[runs] = fopen(filename, "rb");
        load_buffer(bps[runs], load_size, fps[runs]);
    }
    merge(fps, bps, num);
    for (runs = 0; runs < num; runs++) {
        fclose(fps[runs]);
    }
    free(fps);
    free(bps);
}

void merge(FILE** fps, int** bps, int num) {
    while (input_size != 0) {

    }
}

void update_id(char* id) {
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