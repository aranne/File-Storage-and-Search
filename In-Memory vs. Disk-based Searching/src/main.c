#include <stdio.h>
#include "mem_lin.h"

int main(int argc, const char * argv[]) {
    const char* key = argv[1];
    const char* seek = argv[2];
    search(key, seek);    
    return 0;
}