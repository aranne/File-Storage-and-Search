#include "heap.h"

void heapfy(node* array, int size) {
    int i = size / 2;
    while (i >= 1) {
        sink(array, i, size);
        i--;
    }
}

void sink(node* array, int i, int size) {
    while (i <= size / 2) {
        int j = i * 2;
        int k = j + 1;
        int idx;
        if (k <= size && array[k].value <= array[j].value) {
            idx = k;
        } else {
            idx = j;
        }
        if (array[i].value <= array[idx].value) {
            return;
        }
        swap(array, i, idx);
        i = idx;
    }
}

void swap(node* array, int i, int j) {
    node temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void heapfy_array(int* array, int size) {
    int i = size / 2 - 1;
    while (i >= 0) {
        sink_array(array, i, size);
        i--;
    }
}

void sink_array(int* array, int i, int size) {
    while (i < size / 2) {
        int j = i * 2 + 1;
        int k = j + 1;
        int idx;
        if (k < size && array[k] <= array[j]) {
            idx = k;
        } else {
            idx = j;
        }
        if (array[i] <= array[idx]) {
            return;
        }
        swap_array(array, i, idx);
        i = idx;
    }
}

void swap_array(int* array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}