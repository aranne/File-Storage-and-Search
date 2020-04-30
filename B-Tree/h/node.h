#ifndef node_h
#define node_h

#include <stdio.h>

typedef struct _node {
    int value;
    struct _node *next;
    struct _node *prev;
} node;

node* new_node(node* prev, int value, node* next);
void free_node(node* node);

#endif 
