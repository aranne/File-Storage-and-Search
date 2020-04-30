#include <stdio.h>
#include <btree.h>


int main(int argc, const char * argv[]) {
    if (argc != 3) {
        printf("Number of arguments error\n");
        return 0;
    }
    printf("Running\n");
    const char* filename = argv[1];
    const char* order = argv[2];
    init_btree(filename, order);
    return 0;
}