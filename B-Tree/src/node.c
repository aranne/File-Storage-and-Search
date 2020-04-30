#include <stdlib.h>
#include "node.h"

node* new_node(node* prev, int value, node* next) {
    node *n = (node*) malloc(sizeof(node));
    n->value = value;
    n->prev = prev;
    n->next = next;
    return n;
}

void free_node(node* n) {
    free(n);
    n->value = 0;
    n->prev = NULL;
    n->next = NULL;
}