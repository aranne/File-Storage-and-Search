#include <stdlib.h>
#include <node.h>

node_t* new_node(node_t* prev, long value, node_t* next) {
    node_t *node = (node_t*) malloc(sizeof(node));
    node->value = value;
    node->prev = prev;
    node->next = next;
    return node;
}

void free_node(node_t* node) {
    free(node);
    node->value = 0;
    node->prev = NULL;
    node->next = NULL;
}