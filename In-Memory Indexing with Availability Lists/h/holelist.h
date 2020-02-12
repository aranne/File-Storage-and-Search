#ifndef holelist_h
#define holelist_h

#include "arraylist.h"

extern ArrayList holelist;

ArrayList load_holelist(void);
void write_holelist(ArrayList* holelist);
void free_holelist(ArrayList* holelist);
void add_hole(ArrayList* holelist, avail_S hole);
int find_hole(ArrayList* holelist, size_t size);
int peek_hole(ArrayList* holelist, size_t size);
avail_S delete_hole(ArrayList* holelist, int i, size_t size);
void print_holelist(ArrayList* holelist);

#endif