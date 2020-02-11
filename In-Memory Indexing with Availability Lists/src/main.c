#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, const char * argv[]) {
    
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;

    while ((len = getline(&line, &size, stdin)) != EOF) {
        printf("len:%zu\t%s\n", len, line);
        printf("bytes: %zu\n", size);
    }
    free(line);

    return 0;
}