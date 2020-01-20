#include <stdio.h>
#include <string.h>
#include "mem_lin.h"
#include "mem_bin.h"
#include "disk_lin.h"
#include "disk_bin.h"

int main(int argc, const char * argv[]) {
    if (argc != 4) {
        printf("Argument number error\n");
        return 0;
    }
    const char* mode = argv[1];
    const char* key = argv[2];
    const char* seek = argv[3];
    if (strcmp(mode, "--mem-lin") == 0) {
        mem_lin_search(key, seek);
    } else if (strcmp(mode, "--mem-bin") == 0) {
        mem_bin_search(key, seek);
    } else if (strcmp(mode, "--disk-lin") == 0) {
        disk_lin_search(key, seek);
    } else if (strcmp(mode, "--disk-bin") == 0) {
        disk_bin_search(key, seek);
    } else {
        printf("Argument format error\n");
    }
    return 0;
}