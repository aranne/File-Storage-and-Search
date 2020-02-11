#include <stdio.h>
#include "test.h"
#include "array.h"
#include "index.h"
#include "primindex.h"


void test1() {
    Array array = array_create(0);
    array_print(&array);
    int i;
    for (i = 0; i < 10; i++) {
        index_S index = {i, 1};
        array_add(&array, i, index);
    }
    index_S idx1 = {100, 1};
    array_add(&array, array.num, idx1);
    array_delete(&array, 0);
    array_print(&array);
}

void test2() {
    
    Array index = loadindex();
    int i;
    for (i = 0; i < 10; i++) {
        index_S idx = {i, 1};
        addindex(&index, idx);
    }
    printindex(&index);
    writeindex(&index);
}
