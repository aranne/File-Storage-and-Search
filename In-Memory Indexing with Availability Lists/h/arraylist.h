#ifndef arraylist_h
#define arraylist_h

#include "hole.h"

typedef struct {
    avail_S* array;
    int size;
    int num;
} ArrayList;   /* Array for availability list */

ArrayList list_create(int size);
void list_free(ArrayList* a);
int list_size(const ArrayList* a);
int list_num(const ArrayList* a);
avail_S* list_at(const ArrayList* a, int i);
avail_S list_get(const ArrayList* a, int i);
void list_set(ArrayList* a, int i, avail_S hole);
void list_add(ArrayList* a, int i, avail_S hole);
avail_S list_delete(ArrayList* a, int i);
void list_print(const ArrayList* a);

#endif