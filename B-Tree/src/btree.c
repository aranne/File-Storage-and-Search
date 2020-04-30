#include <stdio.h>
#include <stdlib.h>
#include <btree.h>

FILE* fp;
long root;

boolean search_helper(btree_node *node, int key);

void init_btree(const char* filename, const char* order_s) {
    order = atoi(order_s);
    fp = fopen(filename, "r+b" );
    /* If file doesn't exist, set root offset to unknown and create
    * file, otherwise read the root offset at the front of the file */
    if ( fp == NULL ) {
        root = -1;
        fp = fopen( filename, "w+b" );
        fwrite( &root, sizeof( long ), 1, fp );
    } else {
        fread( &root, sizeof( long ), 1, fp );
    }
}

void write_btree() {
    fseek(fp, 0, SEEK_SET);
    fwrite(&root, sizeof(long), 1, fp);
    fclose(fp);
}

boolean search(int key) {
    if (root == -1) {
        printf("Entry with key=%d does not exist\n", key);
        return FALSE;
    }
    btree_node *root = read_btree_node(root);
    boolean find = search_helper(root, key);
    if (find) {
        printf("Entry with key=%d exists\n", key);
    } else {
        printf("Entry with key=%d does not exist\n", key);
    }
    return find;
}

boolean search_helper(btree_node *node, int key) {
    int i = 0;
    while (i < node->n) {
        if (key == node->keys[i]) {
            return TRUE;
        } else if (key < node->keys[i]) {
            break;
        } else {
            i++;
        }
    }
    if (node->child[i] != -1) {
        btree_node *n = read_btree_node(node->child[i]);
        free_btree_node(node);
        return search_helper(n, key);
    } else {
        return FALSE;
    }
}

void add(int key) {
    if (search(key)) {
        printf("Entry with key=%d already exists\n", key);
        return;
    }
    btree_node *node;
    if (root == -1) {
        node = new_btree_node();
        node->n++;
        node->keys[0] = key;
        fseek(fp, 0, SEEK_END);
        root = ftell(fp);
        write_btree_node(node, root);
        return;
    }
    node = read_btree_node(root);

}

result_t add_helper(btree_node* node, int key, long offset) {
    if (isleaf(node)) {
        result_t result = {key, -1};
        if (node->n < order - 1) {  // leaf node has space for new key
            return insert(node, result, offset);
        } else {    // need to split node and promote a key
            return split(node, result, offset);
        }
    } else {
        int i = 0;
        while (i < node->n) {
            if (key < node->keys[i]) {
                break;
            } else {
                i++;
            }
        }
        long child_off = node->child[i];
        btree_node *child = read_btree_node(child_off);
        result_t r = add_helper(child, key, child_off);
        if (r.newchild != -1) {                 // there's a promoted key
            if (node->n < order - 1) {          // parent has space for promoted key
                return insert(node, r, offset);
            } else {                            // need to split node
                
            }
        } else {
            free_btree_node(child);
            return r;
        }
    }
}

result_t insert(btree_node *node, result_t result, long offset) {
    int i = 0;
    while (i < node->n) {
        if (result.promoted < node->keys[i]) {
            break;
        } else {
            i++;
        }
    }
    int insert_pos = i;
    i = node->n;
    if (isleaf(node)) {
        while (i > insert_pos) {
            node->keys[i] = node->keys[i - 1];   // move keys one step right
            i--;
        }
        
    } else {
        while (i > insert_pos) {
            node->keys[i] = node->keys[i - 1];    // move keys one step right
            node->child[i + 1] = node->child[i]; // move child one step right
            i--;
        }
        node->child[insert_pos + 1] = result.newchild;
    }
    node->keys[insert_pos] = result.promoted;
    node->n++;
    write_btree_node(node, offset);
    result_t res = {-1, -1};
    return res;
}

result_t split(btree_node *node, result_t result, long offset) {
    int mid;              /* ceiling of node->n / 2 */
    if (node->n % 2 == 0) {
        mid = node->n / 2;
    } else {
        mid = node->n / 2 + 1;
    }
    btree_node *new_node = new_btree_node();
    int i = 0;
    int* new_keys = malloc( order * sizeof(int));
    // if (isleaf(node)) {
    //     while (i < mid) {
    //         if (result.promoted < node->keys[i]) {
    //             new_keys[i++] = 
    //         }
    //     }
    // } else {

    // }
}