#include <stdio.h>
#include "mem_lin.h"
#include "mem_bin.h"
#include "disk_lin.h"
#include "disk_bin.h"

int main(int argc, const char * argv[]) {
    const char* key = argv[1];
    const char* seek = argv[2];
    mem_lin_search(key, seek);    
    return 0;
}