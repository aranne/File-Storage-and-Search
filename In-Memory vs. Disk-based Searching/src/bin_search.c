#include <stdio.h>
#include "bin_search.h"

int bin_search(int target, Array* a) {
    int* array = a->array;
    int left = 0;
    int right = a->size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == target) {
            return 1;
        } else if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return 0;
}