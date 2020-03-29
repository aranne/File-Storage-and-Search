#include "heap.h"

void swap(int* array, int i, int j);

void heapfy(int* array, int size) {
    int i = size / 2;
    while (i >= 1) {
        sink(array, i, size);
        i--;
    }
}

void sink(int* array, int i, int size) {
    while (i <= size / 2) {
        int j = i * 2;
        int k = j + 1;
        int idx;
        if (k <= size && array[k] >= array[j]) {
            idx = k;
        } else {
            idx = j;
        }
        if (array[i] >= array[idx]) {
            return;
        }
        swap(array, i, idx);
        i = idx;
    }
}

void swap(int* array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
