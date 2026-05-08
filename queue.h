#ifndef QUEUE_H
#define QUEUE_H

#include "arena.h"

typedef struct {
    int task_id;
    uint32_t next_offset;
} QueueNode;

typedef struct {
    uint32_t head_offset;
    uint32_t tail_offset;
    size_t count;
} Queue;

void queue_init(Queue *q);
int enqueue(Arena *arena, Queue *q, int task_id);
int dequeue(Arena *arena, Queue *q, int *task_id_out);
void queue_display(Arena *arena, Queue *q);

#endif