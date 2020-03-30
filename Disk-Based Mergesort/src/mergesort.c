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
void merge_runs(const char* input_f, int num, char* id, char* mode);
void load_run(int r, int* buffer, int load_size, FILE* fp, run* runs);
void merge(FILE** fps, run* runs, int num, const char* input_f, char* mode);
void write_output(const char* input_f, char* mode, int size, char* id, int* buffer);

void basic_mergesort(const char* input_f, const char* output_f) {
    input_fp = fopen(input_f, "rb");
    output_fp = fopen(output_f, "wb");
    if (input_fp == NULL || output_fp == NULL) {
        printf("Open file failed\n");
        return;
    }
    int num = create_runs(input_f);
    char id[4] = "000";
    char* mode = "output";
    merge_runs(input_f, num, id, mode);
    fclose(input_fp);
    fclose(output_fp);
}

void multistep_mergesort(const char* input_f, const char* output_f) {
    input_fp = fopen(input_f, "rb");
    output_fp = fopen(output_f, "wb");
    if (input_fp == NULL || output_fp == NULL) {
        printf("Open file failed\n");
        return;
    }
    int num = create_runs(input_f);

}

int create_runs(const char* input_f) {
    int load_size;
    char id[4] = "000";
    int r = 0;
    while ( (load_size = load_buffer(input, buffer_size, input_fp)) != 0) {
        sort_buffer(input, load_size);
        write_output(input_f, "runs", load_size, id, input);
        update_id(id);
        r++;
    }
    return r;
}

void merge_runs(const char* input_f, int num, char* id, char* mode) {
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
    merge(fps, runs, num, input_f, mode);
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

void merge(FILE** fps, run* runs, int num, const char* input_f, char* mode) {
    int load_size = buffer_size / num;
    // heap starts at index 1
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
    char id[4] = "000";
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
            write_output(input_f, mode, output_size, id, output);
            update_id(id);
            output_size = 0;
        }
    }
    free(heap);
}

void write_output(const char* input_f, char* mode, int size, char* id, int* buffer) {
    if (strcmp(mode, "output") == 0) {
        fwrite(buffer, size, sizeof(int), output_fp);
    } else if (strcmp(mode, "runs") == 0) {
        char filename[40];
        strcpy(filename, input_f);
        strcat(filename, ".");
        strcat(filename, id);
        write_buffer(buffer, size, filename);
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