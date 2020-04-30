#ifndef node_h
#define node_h

#include <stdio.h>

typedef struct _node {
    long value;
    struct _node *next;
    struct _node *prev;
} node_t;

node_t* new_node(node_t* prev, long value, node_t* next);
void free_node(node_t* node);

#endif 
