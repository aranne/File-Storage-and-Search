#include <stdio.h>
#include <sys/time.h>
#include "mem_lin.h"
#include "load.h"
#include "Array.h"
#include "lin_search.h"
#include "time_sub.h"
#include "output.h"

void mem_lin_search(const char* kp, const char* sp) {
    Array seek = load(sp);
    Array hit = array_create(seek.size);
    
    // record start time
    struct timeval start;
    gettimeofday(&start, NULL);

    Array key = load(kp);
    
    int i;
    for (i = 0; i < seek.size; ++i) {
        int target = seek.array[i];
        int find = lin_search(target, key.array, key.size);
        if (find) {
            hit.array[i] = 1;
        } else {
            hit.array[i] = 0;
        }
    }

    // record end time
    struct timeval end;
    gettimeofday(&end, NULL);

    struct timeval exec;
    timeval_subtract(&exec, &end, &start);

    // output 
    print_output(&seek, &hit, exec);
    

    // free malloc address
    array_free(&key);
    array_free(&seek);
    array_free(&hit);
}

