#include <stdio.h>
#include <sys/time.h>
#include "disk_bin.h"
#include "load.h"
#include "Array.h"
#include "time_sub.h"
#include "output.h"

void disk_bin_search(const char* kp, const char* sp) {
    Array seek = load(sp);
    Array hit = array_create(seek.size);

    // record start time
    struct timeval start;
    gettimeofday(&start, NULL);

    FILE* fp = fopen(kp, "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp) / sizeof(int);
        int i;
        for (i = 0; i < seek.size; ++i) {
            int target = seek.array[i];
            int find = 0, res = 0;
            int left = 0, right = size;
            while (left < right) {
                int mid = left + ((right - left) >> 1);
                fseek(fp, mid * sizeof(int), SEEK_SET);
                fread(&res, sizeof(int), 1, fp);
                if (res == target) {
                    find = 1;
                    break;
                } else if (res < target) {
                    left = mid + 1;
                } else {
                    right = mid;
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

    struct timeval exec;
    timeval_subtract(&exec, &end, &start);
    
    // output 
    print_output(&seek, &hit, exec);

    // free malloc address
    array_free(&seek);
    array_free(&hit);
}