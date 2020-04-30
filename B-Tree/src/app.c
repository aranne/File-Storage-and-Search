#include <stdio.h>
#include <btree.h>


int main(int argc, const char * argv[]) {
    if (argc != 3) {
        printf("Number of arguments error\n");
        return 0;
    }
    const char* filename = argv[1];
    const char* order = argv[2];
    init_btree(filename, order);
    test_split2();
    return 0;
}