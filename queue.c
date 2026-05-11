#include "queue.h"
#include <stdio.h>

void queue_init(Queue *q) {
    q->head_offset = 0;
    q->tail_offset = 0;
    q->count = 0;
}

int enqueue(Arena *arena, Queue *q, int task_id) {
    uint32_t new_offset = arena_alloc(arena, sizeof(QueueNode));
    if (new_offset == 0) {
        return 0;
    }
    QueueNode *new_node = (QueueNode*)arena_get(arena, new_offset);
    new_node->task_id = task_id;
    new_node->next_offset = 0;

    if (q->tail_offset == 0) {
        q->head_offset = new_offset;
    }
    else {
        QueueNode *old_tail = (QueueNode*)arena_get(arena, q->tail_offset);
        old_tail->next_offset = new_offset;
    } // O(1)
    q->tail_offset = new_offset;
    q->count++;
    return 1;
}

int dequeue(Arena *arena, Queue *q, int *task_id_out) {
    if (q->head_offset == 0) {
        return 0;
    }
    QueueNode *head_node = (QueueNode*)arena_get(arena, q->head_offset);
    *task_id_out = head_node->task_id;
    q->head_offset = head_node->next_offset;

    if (q->head_offset == 0) {
        q->tail_offset = 0;
    }
    q->count--;
    return 1;
}

void queue_display(Arena *arena, Queue *q) {
    uint32_t current_offset = q->head_offset;
    
    printf("> VISUALISASI QUEUE\n", q->count);
    if (current_offset == 0) {
        printf("queue kosong\n");
        return;
    }
    while (current_offset != 0) {
        QueueNode *current_node = (QueueNode*)arena_get(arena, current_offset);
        printf("[ID:%d, Off:%u] -> ", current_node->task_id, current_offset);
        current_offset = current_node->next_offset;
    }
    printf("NULL\n");
}