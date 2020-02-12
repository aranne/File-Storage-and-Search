#include <stdio.h>
#include "interface.h"
#include "test.h"

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        printf("Argument number error\n");
        return 0;
    }
    const char* m = argv[1];
    const char* fn = argv[2];
    initialize(m, fn);
    // test1();
    // test2();
    test3();
    return 0;
}