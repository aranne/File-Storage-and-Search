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
