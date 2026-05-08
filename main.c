#include "arena.h"
#include "queue.h"
#include <stdio.h>

void process_batch(Arena *arena, Queue *q) {
    printf("\n> MULAI BATCH PROCESSING %zu TUGAS\n", q->count);
    int task_id;

    while (dequeue(arena, q, &task_id)) {
        printf("task ID: %d berhasil diproses\n", task_id);
    }
    arena_reset(arena);
    queue_init(q);
}

int main() {
    Arena *arena = arena_init(64);
    Queue job_queue;
    queue_init(&job_queue);

    enqueue(arena, &job_queue, 1);
    enqueue(arena, &job_queue, 2);
    enqueue(arena, &job_queue, 3);
    enqueue(arena, &job_queue, 4);
    enqueue(arena, &job_queue, 5);
    
    arena_dump(arena); 
    queue_display(arena, &job_queue);
    
    process_batch(arena, &job_queue);
    arena_dump(arena);
    queue_display(arena, &job_queue);

    return 0;
}