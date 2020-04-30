#include <stdio.h>
#include <stdlib.h>
#include <queue.h>

queue_t create_queue(void) {
    queue_t queue;
    node_t *sentinel = new_node(NULL, -1, NULL);
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    queue.len = 0;
    queue.sentinel = sentinel;
    return queue;
}

void free_queue(queue_t *queue) {
    node_t *sen = queue->sentinel;
    node_t *p = sen->next;
    while (p != sen) {
        node_t *tmp = p->next;
        free_node(p);
        p = tmp;
    }
    free_node(sen);
    queue->len = 0;
    queue->sentinel = NULL;
}

void add_queue(queue_t *queue, long value) {
    node_t *sen = queue->sentinel;
    node_t *node = new_node(sen->prev, value, sen);
    sen->prev->next = node;
    sen->prev = node;
    queue->len++;
}

long poll_queue(queue_t *queue) {
    node_t *sen = queue->sentinel;
    node_t *target = sen->next;
    if (target != sen) {
        long res = target->value;
        sen->next = target->next;
        target->next->prev = sen;
        free_node(target);
        queue->len--;
        return res;
    } else {
        return -1;
    }
}

boolean isempty_queue(queue_t *queue) {
    return queue->len == 0;
}