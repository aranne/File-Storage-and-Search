#include <stdio.h>
#include <string.h>
#include "mergesort.h"
#include "time_sub.h"

int main(int argc, const char * argv[]) {
    if (argc != 4) {
        printf("Argument number error\n");
        return 0;
    }
    const char* mode = argv[1];
    const char* input = argv[2];
    const char* output = argv[3];
    struct timeval start;
    struct timeval end;
    struct timeval exec;
    if (strcmp(mode, "--basic") == 0) {
        gettimeofday(&start, NULL);
        basic_mergesort(input, output);
        gettimeofday(&end, NULL);
    } else if (strcmp(mode, "--multistep") == 0) {
        gettimeofday(&start, NULL);
        multistep_mergesort(input, output);
        gettimeofday(&end, NULL);
    } else if (strcmp(mode, "--replacement") == 0) {
        gettimeofday(&start, NULL);
        replacement_mergesort(input, output);
        gettimeofday(&end, NULL);
    } else {
        printf("Argument name error\n");
        return 0;
    }
    timeval_subtract(&exec, &end, &start);
    printf( "Time: %ld.%06ld", exec.tv_sec, exec.tv_usec );
    return 0;
}