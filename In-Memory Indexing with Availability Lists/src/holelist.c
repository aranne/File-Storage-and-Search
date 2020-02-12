#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "holelist.h"
#include "db.h"

const char* mode;
const char* listname;
void append_hole(ArrayList* holelist, avail_S hole);
long find_first_hole(ArrayList* holelist, size_t size);
long find_best_hole(ArrayList* holelist, size_t size);
long find_worst_hole(ArrayList* holelist, size_t size);
int compareHoleACS (const void * a, const void * b);
int compareHoleDCS (const void * a, const void * b);

ArrayList load_holelist() {
    ArrayList a = list_create(0);
    FILE* fp = fopen(listname, "r+b");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        size_t num = ftell(fp) / sizeof(avail_S);
        a = list_create((int) num);
        fseek(fp, 0, SEEK_SET);
        size_t read_num = fread(a.array, sizeof(avail_S), num, fp);
        if (num != read_num) {
            list_free(&a);
            printf("Read Index Error\n");
        }
        a.num = (int) num;
        a.size = (int) num;
        fclose(fp);
    }
    return a;
}

void write_holelist(ArrayList* holelist) {
    FILE* fp = fopen(listname, "w+b");
    fseek(fp, 0, SEEK_SET);
    fwrite(holelist->array, sizeof(avail_S), holelist->num, fp);
    free_holelist(holelist);
    fclose(fp);
}

void free_holelist(ArrayList* holelist) {
    list_free(holelist);
}

void add_hole(ArrayList* holelist, avail_S hole) {
    if (strcmp(mode, "--first-fit") == 0) {
        append_hole(holelist, hole);
    } else if (strcmp(mode, "--best-fit") == 0) {
        append_hole(holelist, hole);
        qsort((void*) holelist->array, (size_t) holelist->num, sizeof(avail_S), compareHoleACS);
    } else if (strcmp(mode, "--worst-fit") == 0) {
        append_hole(holelist, hole);
        qsort((void*) holelist->array, (size_t) holelist->num, sizeof(avail_S), compareHoleDCS);
    } else {
        printf("Input Mode Error\n");
    }
}

int find_hole(ArrayList* holelist, size_t size) {
    int i;
    avail_S* array = holelist->array;
    for (i = 0; i < holelist->num; i++) {
        if (array[i].size >= size) return i;
    }
    return -1;
}

int peek_hole(ArrayList* holelist, size_t size) {
    if (holelist->num == 0) return -1;
    avail_S* array = holelist->array;
    if (array[0].size >= size) return 0;
    return -1;
}

avail_S delete_hole(ArrayList* holelist, int i, size_t size) {
    return list_delete(holelist, i);
}

/* ###################################################

############ HELPER FUCTIONS #########################

#################################################### */

void append_hole(ArrayList* holelist, avail_S hole) {
    list_add(holelist, holelist->num, hole);
}

int compareHoleACS (const void * a, const void * b)
{
  if ( ((avail_S*) a)->size < ((avail_S*) b)->size ) return -1;
  else if ( ((avail_S*) a)->size == ((avail_S*) b)->size ) {
      if ( ((avail_S*) a)->offset < ((avail_S*) b)->offset ) return -1;
      if ( ((avail_S*) a)->offset == ((avail_S*) b)->offset ) return 0;
      if ( ((avail_S*) a)->offset > ((avail_S*) b)->offset ) return 1;
  }
  return 1;
}

int compareHoleDCS (const void * a, const void * b)
{
  if ( ((avail_S*) a)->size < ((avail_S*) b)->size ) return 1;
  else if ( ((avail_S*) a)->size == ((avail_S*) b)->size ) {
      if ( ((avail_S*) a)->offset < ((avail_S*) b)->offset ) return 1;
      if ( ((avail_S*) a)->offset == ((avail_S*) b)->offset ) return 0;
      if ( ((avail_S*) a)->offset > ((avail_S*) b)->offset ) return -1;
  }
  return -1;
}

void print_holelist(ArrayList* holelist) {
    printf("Availability:\n");
    int i;
    int size = 0;
    int num = holelist->num;
    avail_S* array = holelist->array;
    for (i = 0; i < holelist->num; i++) {
        size += (int) array[i].size;
        printf( "size=%d: offset=%ld\n", (int) array[i].size, array[i].offset);
    }
    printf( "Number of holes: %d\n", num );
    printf( "Hole space: %d\n", size );
}