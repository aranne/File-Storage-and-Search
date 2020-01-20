#include <stdio.h>
#include "lin_search.h"

int lin_search(int target, int* array, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (array[i] == target) {
            return 1;
        }
    }
    return 0;
}