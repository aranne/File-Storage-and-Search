#include <stdio.h>
#include <sys/time.h>
#include "load.h"
#include "mem_bin.h"
#include "Array.h"

void mem_bin_search(const char* kp, const char* sp) {
    // record start time
    struct timeval tm;
    gettimeofday(&tm, NULL);
    long int start_sec = tm.tv_sec;
    long int start_usec = tm.tv_usec;

    Array key = load(kp);
    Array seek = load(sp);
    Array hit = array_create(seek.size);
    // int k;
    // for (k = 0; k < seek.size; ++k) {
    //     int target = seek.array[k];

    // }
    

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

