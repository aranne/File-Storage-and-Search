#include <stdio.h>
#include <stdlib.h>
#include "mem_lin.h"
#include "load.h"
#include "Array.h"

void search(const char* kp, const char* sp) {
    Array key = load(kp);
    Array seek = load(sp);
    Array hit = array_create(seek.size);
    int i, j;
    for (i = 0; i < seek.size; ++i) {
        int target = seek.array[i];
        int find = 0;
        for (j = 0; j < key.size; ++j) {
            int item = key.array[j];
            if (item == target) {
                find = 1;
                break;
            }
        }
        if (find) {
            hit.array[i] = 1;
            printf( "%12d: Yes\n", target);
        } else {
            hit.array[i] = 0;
            printf( "%12d: No\n", target);
        }
    }

    // free malloc address
    array_free(&key);
    array_free(&seek);
    array_free(&hit);
}

