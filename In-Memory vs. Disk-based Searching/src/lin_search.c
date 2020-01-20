#include <stdio.h>
#include "lin_search.h"

int lin_search(int target, Array* a) {
    int i;
    for (i = 0; i < a->size; ++i) {
        if (a->array[i] == target) {
            return 1;
        }
    }
    return 0;
}