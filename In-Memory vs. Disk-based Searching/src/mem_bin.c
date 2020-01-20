#include <stdio.h>
#include <sys/time.h>
#include "load.h"
#include "mem_bin.h"
#include "Array.h"
#include "bin_search.h"

void mem_bin_search(const char* kp, const char* sp) {
    // record start time
    struct timeval tm;
    gettimeofday(&tm, NULL);
    long int start_sec = tm.tv_sec;
    long int start_usec = tm.tv_usec;

    Array key = load(kp);
    Array seek = load(sp);
    Array hit = array_create(seek.size);
    int i;
    for (i = 0; i < seek.size; ++i) {
        int target = seek.array[i];
        int find = bin_search(target, &key);
        if (find) {
            hit.array[i] = 1;
            printf( "%12d: Yes\n", target);
        } else {
            hit.array[i] = 0;
            printf( "%12d: No\n", target);
        }
    }

    // record end time
    gettimeofday(&tm, NULL);
    long int end_sec = tm.tv_sec;
    long int end_usec = tm.tv_usec;
    printf("Time: %ld.%06ld\n", end_sec - start_sec, end_usec - start_usec);

    // free malloc address
    array_free(&key);
    array_free(&seek);
    array_free(&hit);
}

