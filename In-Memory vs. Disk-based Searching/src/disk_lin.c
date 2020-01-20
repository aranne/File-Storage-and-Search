#include <stdio.h>
#include <sys/time.h>
#include "load.h"
#include "disk_lin.h"
#include "Array.h"
#include "time_sub.h"


void disk_lin_search(const char* kp, const char* sp) {
    Array seek = load(sp);
    Array hit = array_create(seek.size);
    FILE* fp = fopen(kp, "rb");

    // record start time
    struct timeval start;
    gettimeofday(&start, NULL);
    
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp) / sizeof(int);
        int i, j;
        for (i = 0; i < seek.size; ++i) {
            int target = seek.array[i];
            int find = 0, res = 0;
            for (j = 0; j < size; ++j) {
                fseek(fp, j * sizeof(int), SEEK_SET);
                fread(&res, sizeof(int), 1, fp);
                if (res == target) {
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
    } else {
        printf("Open file failed\n");
    }

    // record end time
    struct timeval end;
    gettimeofday(&end, NULL);
    struct timeval exec;
    timeval_subtract(&exec, &end, &start);
    printf("Time: %ld.%06ld\n", exec.tv_sec, exec.tv_usec);

    // free malloc address
    array_free(&seek);
    array_free(&hit);
}