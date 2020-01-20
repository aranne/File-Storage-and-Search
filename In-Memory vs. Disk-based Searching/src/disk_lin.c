#include <stdio.h>
#include <sys/time.h>
#include "load.h"
#include "disk_lin.h"
#include "Array.h"
#include "time_sub.h"


void disk_lin_search(const char* kp, const char* sp) {
    Array seek = load(sp);
    Array hit = array_create(seek.size);

    // record start time
    struct timeval start;
    gettimeofday(&start, NULL);
    
    FILE* fp = fopen(kp, "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp) / sizeof(int);
        int i, j;
        for (i = 0; i < seek.size; ++i) {
            int target = seek.array[i];
            int find = 0, res = 0;
            fseek(fp, 0, SEEK_SET);
            for (j = 0; j < size; ++j) {
                fread(&res, sizeof(int), 1, fp);
                if (res == target) {
                    find = 1;
                    break;
                }
            }
            if (find) {
                hit.array[i] = 1;
            } else {
                hit.array[i] = 0;
            }
        }
    } else {
        printf("Open file failed\n");
    }
    fclose(fp);

    // record end time
    struct timeval end;
    gettimeofday(&end, NULL);

    // output
    int k;
    for (k = 0; k < seek.size; ++k) {
        if (hit.array[k] == 1) {
            printf( "%12d: Yes\n", seek.array[k]);
        } else {
            printf( "%12d: No\n", seek.array[k]);
        }
    }
    struct timeval exec;
    timeval_subtract(&exec, &end, &start);
    printf("Time: %ld.%06ld\n", (long) exec.tv_sec, (long) exec.tv_usec);

    // free malloc address
    array_free(&seek);
    array_free(&hit);
}