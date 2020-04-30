#ifndef queue_h
#define queue_h

#include <node.h>

typedef struct {
    node_t *sentinel;
    int len;
} queue_t;

queue_t create_queue(void);
void free_queue(queue_t *queue);

#endif