#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mem_lin.h"
#include "load.h"
#include "Array.h"

void search(const char* kp, const char* sp) {
    // record start time
    struct timeval tm;
    gettimeofday(&tm, NULL);
    long int start_sec = tm.tv_sec;
    long int start_usec = tm.tv_usec;

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

    // record end time
    gettimeofday(&tm, NULL);
    long int end_sec = tm.tv_sec;
    long int end_usec = tm.tv_usec;
    printf("Time: %ld.%06ld\n", end_sec - start_sec, end_usec - start_usec);
}

