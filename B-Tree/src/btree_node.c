#include <stdio.h>
#include <stdlib.h>
#include <btree_node.h>
#include <btree.h>

// typedef struct {
//     int n;        /* Number of keys in node */
//     int *keys;    /* Node's keys */
//     long *child;   /* Node's child subtree offsets */
// } btree_node;

btree_node* new_btree_node() {
    btree_node* node = malloc(sizeof(btree_node));
    node->n = 0;
    node->keys = (int *) malloc( (order - 1) * sizeof( int ) ); 
    node->child = (long *) malloc( order * sizeof( long ) );
    int i;
    for (i = 0; i < order - 1; i++) {
        node->keys[i] = -1;
    }
    for (i = 0; i < order; i++) {
        node->child[i] = -1;
    }
    return node;
}

btree_node* read_btree_node(long offset) {
    fseek(fp, offset, SEEK_SET);
    btree_node* node = new_btree_node();
    fread(&(node->n), sizeof(int), 1, fp);
    fread(node->keys, sizeof(int), order - 1, fp);
    fread(node->child, sizeof(long), order, fp);
    return node;
}

void write_btree_node(btree_node *node, long offset) {
    fseek(fp, offset, SEEK_SET);
    fwrite(&(node->n), sizeof(int), 1, fp);
    fwrite(node->keys, sizeof(int), order - 1, fp);
    fwrite(node->child, sizeof(long), order, fp);
    free_btree_node(node);
}

void free_btree_node(btree_node *node) {
    free(node);
    node->n = 0;
    node->keys = NULL;
    node->child = NULL;
}

boolean isleaf(btree_node *node) {
    return node->child[0] == -1;
}