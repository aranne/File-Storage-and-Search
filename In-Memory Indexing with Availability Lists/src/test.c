#include <stdio.h>
#include "test.h"
#include "array.h"
#include "index.h"


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
