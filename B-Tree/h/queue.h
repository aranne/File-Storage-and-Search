#ifndef queue_h
#define queue_h

#include <btree_node.h>
#include <node.h>

typedef struct {
    node_t *sentinel;
    int len;
} queue_t;

queue_t create_queue(void);
void free_queue(queue_t *queue);
void add_queue(queue_t *queue, long value);
long poll_queue(queue_t *queue);
boolean isempty_queue(queue_t *queue);

#endif