#include <stdio.h>
#include "test.h"
#include "primindex.h"
#include "holelist.h"


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

void test3() {
    ArrayList array = list_create(0);
    list_print(&array);
    int i;
    for (i = 0; i < 10; i++) {
        avail_S hole = {i, 1};
        list_add(&array, i, hole);
    }
    avail_S hole1 = {100, 1};
    list_add(&array, array.num, hole1);
    list_delete(&array, 0);
    list_print(&array);
}

void test2() {
    
    Array index = load_index();
    int i;
    for (i = 0; i < 10; i++) {
        index_S idx = {i * i, 1};
        addindex(&index, idx);
    }
    index_S idx1 = {26, 1};
    addindex(&index, idx1);
    printindex(&index);
    array_print(&index);
    write_index(&index);
}

void test4() {
    ArrayList holelist = load_holelist();
    int i;
    for (i = 0; i < 10; i++) {
        avail_S hole = {i, 1};
        add_hole(&holelist, hole);
    }
    print_holelist(&holelist);
    write_holelist(&holelist);
}
