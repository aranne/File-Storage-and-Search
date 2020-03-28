#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    if (argc != 4) {
        printf("Argument number error\n");
        return 0;
    }
    const char* mode = argv[1];
    const char* input = argv[2];
    const char* output = argv[3];
    if (strcmp(mode, "--basic") == 0) {

    } else if (strcmp(mode, "--multistep") == 0) {

    } else if (strcmp(mode, "--replacement") == 0) {

    } else {
        printf("Argument name error\n");
        return 0;
    }
    return 0;
}