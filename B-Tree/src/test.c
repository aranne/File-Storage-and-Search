#include <stdio.h>
#include <btree.h>
#include <test.h>

result_t insert(btree_node *node, result_t result, long offset);
result_t split(btree_node *node, result_t result, long offset);

void test_insert1() {
    btree_node *node = new_btree_node();
    node->n = 2;
    node->keys[0] = 1;
    node->keys[1] = 5;
    node->child[0] = 10;
    node->child[1] = 20;
    node->child[2] = 30;
    result_t res = {0, 100};
    insert(node, res, 0);
    node = read_btree_node(0);
    print_node(node);
}

void test_insert2() {
    btree_node *node = new_btree_node();
    node->n = 2;
    node->keys[0] = 1;
    node->keys[1] = 5;
    result_t res = {0, 100};
    insert(node, res, 0);
    node = read_btree_node(0);
    print_node(node);
}

void test_split1() {
    btree_node *node = new_btree_node();
    node->n = 3;
    node->keys[0] = 1;
    node->keys[1] = 5;
    node->keys[2] = 10;
    result_t r = {0, 100};
    result_t res = split(node, r, 0);
    node = read_btree_node(0);
    btree_node *new_node = read_btree_node(res.newchild);
    print_node(node);
    print_node(new_node);
    printf("Mid: %d\n", res.promoted);
}

void test_split2() {
    btree_node *node = new_btree_node();
    node->n = 3;
    node->keys[0] = 1;
    node->keys[1] = 5;
    node->keys[2] = 10;
    node->child[0] = 50;
    node->child[1] = 55;
    node->child[2] = 60;
    node->child[3] = 65;
    result_t r = {0, 100};
    result_t res = split(node, r, 0);
    node = read_btree_node(0);
    btree_node *new_node = read_btree_node(res.newchild);
    print_node(node);
    print_node(new_node);
    printf("Mid: %d\n", res.promoted);
    printf("Offset: %ld\n", res.newchild);
}

