#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"
#include "buffer.h"
#include "heap.h"

FILE* input_fp = NULL;
FILE* output_fp = NULL;

void update_id(char * id);
int create_runs(const char* input_f);
void merge_runs(const char* input_f, int num);
void load_run(int r, int* buffer, int load_size, FILE* fp, run* runs);
void merge(FILE** fps, run* runs, int num);

void basic_mergesort(const char* input_f, const char* output_f) {
    input_fp = fopen(input_f, "rb");
    output_fp = fopen(output_f, "wb");
    if (input_fp == NULL || output_fp == NULL) {
        printf("Open file failed\n");
        return;
    }
    int r = create_runs(input_f);
    merge_runs(input_f, r);
    fclose(input_fp);
    fclose(output_fp);
}

int create_runs(const char* input_f) {
    int load_size;
    char id[4] = "000";
    char filename[30];
    int r = 0;
    while ( (load_size = load_buffer(input, buffer_size, input_fp)) != 0) {
        sort_buffer(input, load_size);
        strcpy(filename, input_f);
        strcat(filename, ".");
        strcat(filename, id);
        write_buffer(input, load_size, filename);
        update_id(id);
        r++;
    }
    return r;
}

void merge_runs(const char* input_f, int num) {
    char id[4] = "000";
    char filename[30];
    int r;
    FILE** fps = (FILE**) malloc(num * sizeof(FILE*));
    run* runs = (run*) malloc(num * sizeof(run));
    int load_size = buffer_size / num;
    int* bp = input;
    for (r = 0; r < num; r++) {
        strcpy(filename, input_f);
        strcat(filename, ".");
        strcat(filename, id);
        update_id(id);
        fps[r] = fopen(filename, "rb");
        load_run(r, bp, load_size, fps[r], runs);
        bp += load_size;
    }
    merge(fps, runs, num);
    for (r = 0; r < num; r++) {
        fclose(fps[r]);
    }
    free(fps);
    free(runs);
}

void load_run(int r, int* buffer, int load_size, FILE* fp, run* runs) {
    int read_size = load_buffer(buffer, load_size, fp);
    run new_run = {read_size, buffer - input, buffer};
    runs[r] = new_run;
}

void merge(FILE** fps, run* runs, int num) {
    int load_size = buffer_size / num;
    node* heap = (node*) malloc((num + 1) * sizeof(node));
    int heap_size = 0;
    int r;
    for (r = 0; r < num; r++) {
        node new_n = {input[runs[r].index++], r};
        heap[r + 1] = new_n;
        heap_size++;
        runs[r].size--;
    }
    heapfy(heap, heap_size);
    int output_size = 0;
    while (heap_size != 0) {
        output[output_size++] = heap[1].value;
        int r = heap[1].num;
        heap_size--;
        if (runs[r].size != 0) {
            node next_node = {input[runs[r].index++], r};
            heap[1] = next_node;
            heap_size++;
            sink(heap, 1, heap_size);
            runs[r].size--;
            if (runs[r].size == 0) {
                load_run(r, runs[r].start, load_size, fps[r], runs);
            }
        } else {
            swap(heap, 1, 1 + heap_size);
            sink(heap, 1, heap_size);
        }
        if (output_size == buffer_size || heap_size == 0) {
            fwrite(output, output_size, sizeof(int), output_fp);
            output_size = 0;
        }
    }
    free(heap);
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