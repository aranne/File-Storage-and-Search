#include <stdio.h>
#include <stdlib.h>
#include <btree.h>

FILE* fp;
long root;
int order;

boolean search_helper(btree_node *node, int key);
result_t add_helper(btree_node* node, int key, long offset);
result_t insert(btree_node *node, result_t result, long offset);
result_t split(btree_node *node, result_t result, long offset);


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

void close_btree() {
    fseek(fp, 0, SEEK_SET);
    fwrite(&root, sizeof(long), 1, fp);
    fclose(fp);
}

boolean search(int key, boolean print) {
    if (root == -1) {
        if (print) {
            printf("Entry with key=%d does not exist\n", key);
        }
        return FALSE;
    }
    btree_node *root_node = read_btree_node(root);
    boolean find = search_helper(root_node, key);
    if (find) {
        if (print) {
            printf("Entry with key=%d exists\n", key);
        }
    } else {
        if (print) {
            printf("Entry with key=%d does not exist\n", key);
        }
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
        free_btree_node(node);
        return FALSE;
    }
}

void add(int key) {
    if (search(key, FALSE)) {
        printf("Entry with key=%d already exists\n", key);
        return;
    }
    btree_node *root_node;
    if (root == -1) {
        root_node = new_btree_node();
        root_node->n++;
        root_node->keys[0] = key;
        fseek(fp, 0, SEEK_END);
        root = ftell(fp);
        write_btree_node(root_node, root);
        return;
    }
    root_node = read_btree_node(root);
    result_t res = add_helper(root_node, key, root);
    if (res.newchild != -1) {              // create a new root node
        root_node = new_btree_node();
        root_node->n++;
        root_node->keys[0] = res.promoted;
        root_node->child[0] = root;
        root_node->child[1] = res.newchild;
        fseek(fp, 0, SEEK_END);
        root = ftell(fp);
        write_btree_node(root_node, root);
    }
    return;
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
                return split(node, r, offset);
            }
        } else {
            free_btree_node(node);
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
    while (i > insert_pos) {
        node->keys[i] = node->keys[i - 1];    // move keys one step right
        if (!isleaf(node)) {
            node->child[i + 1] = node->child[i]; // move child one step right
        }
        i--;
    }
    node->keys[insert_pos] = result.promoted;
    node->n++;
    if (!isleaf(node)) {
        node->child[insert_pos + 1] = result.newchild;
    }
    write_btree_node(node, offset);
    result_t res = {-1, -1};
    return res;
}

/* node->n == order-1, need to be split */
result_t split(btree_node *node, result_t result, long offset) {
    /* insert new key into a new array & child_array */
    int* array = (int*) malloc( order * sizeof(int));
    long* child_array;
    if (!isleaf(node)) {
        child_array = (long*) malloc((order + 1) * sizeof(long));
        child_array[0] = node->child[0];
    }
    int i = 0, output = 0;
    boolean unused = TRUE;
    while (i < node->n) {
        if (unused && result.promoted < node->keys[i]) {
            unused = FALSE;
            array[output] = result.promoted;
            if (!isleaf(node)) {
                child_array[output + 1] = result.newchild;
            }
            output++;
        } else {
            array[output] = node->keys[i];
            if (!isleaf(node)) {
                child_array[output + 1] = node->child[i + 1];
            }
            output++;
            i++;
        }
    }
    if (unused) {
        array[output] = result.promoted;
        if (!isleaf(node)) {
            child_array[output + 1] = result.newchild;
        }
    }
    /* start spliting */
    btree_node *new_node = new_btree_node();
    int mid = order / 2;
    node->n = mid;                 // left size
    new_node->n = order - 1 - mid; // right size = total - 1 - left

    i = 0;
    int old_idx = 0, new_idx = 0;
    while (i < order) {
        if (i < mid) {
            node->keys[old_idx] = array[i];
            if (!isleaf(node)) {
                node->child[old_idx] = child_array[i];
            }
            old_idx++;
            i++;
        } else if (i == mid) {
            if (!isleaf(node)) {
                node->child[old_idx] = child_array[i];
            }
            i++;
        } else {
            new_node->keys[new_idx] = array[i];
            if (!isleaf(node)) {
                new_node->child[new_idx] = child_array[i];
            }
            new_idx++;
            i++;
        }
    }
    free(array);
    if (!isleaf(node)) {
        new_node->child[new_idx] = child_array[i];
        free(child_array);
    }
    int promoted = array[mid];
    write_btree_node(node, offset);
    fseek(fp, 0, SEEK_END);
    int new_offset = ftell(fp);
    write_btree_node(new_node, new_offset);
    result_t res = {promoted, new_offset};
    return res;
}

void print_btree(void) {
    if (root == -1) {
        printf("B-Tree is empty\n");
    }
    btree_node *node = read_btree_node(root);
    
}