#ifndef btree_node_h
#define btree_node_h

#include <stdio.h>

extern int order;  /* B-tree order */

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct {
    int n;        /* Number of keys in node */
    int *keys;    /* Node's keys */
    long *child;   /* Node's child subtree offsets */
} btree_node;


btree_node* new_btree_node(void);
btree_node* read_btree_node(long offset);
void write_btree_node(btree_node *node, long offset);
void free_btree_node(btree_node *node);
boolean isleaf(btree_node *node);
void print_node(btree_node *node);

#endif