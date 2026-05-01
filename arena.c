#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arena* arena_init(size_t size) {
    Arena *arena = (Arena*)malloc(sizeof(Arena));
    arena->buffer = (uint8_t*)malloc(size);
    memset(arena->buffer, 0, size);
    arena->size = size;
    arena->offset = 0;
    return arena;
}

uint32_t arena_alloc(Arena *arena, size_t size) {
    if (arena->offset + size > arena->size) {
        return 0; 
    }
    uint32_t current_offset = (uint32_t)arena->offset;
    arena->offset += size;
    return current_offset;
}

void* arena_get(Arena *arena, uint32_t offset) {
    if (offset >= arena->size) return NULL;
    return (void*)(arena->buffer + offset);
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
    memset(arena->buffer, 0, arena->size);
}

void arena_dump(Arena *arena) {
    printf("\n> ARENA DUMP (Used: %zu/%zu) \n", arena->offset, arena->size);
    int cols = 32;
    printf("[");
    for (size_t i = 0; i < arena->size; i++) {
        if (i % cols == 0) {
            printf("%04zu | ", i);
        }
        if (i < arena->offset) {
            printf("+");
        }
        else {
            printf("-");
        }
        if (i == arena->size-1) {
            continue;
        }
        else if ((i + 1) % cols == 0) {
            printf("]\n[");
        }
    }
    printf("]");
    printf("\n\n");
}

uint32_t list_prepend(Arena *arena, uint32_t head_offset, int value) {
    uint32_t new_node_offset = arena_alloc(arena, sizeof(Node));

    if (new_node_offset == 0) return head_offset; 

    Node *new_node = (Node*)arena_get(arena, new_node_offset);
    new_node->value = value;
    new_node->next_offset = head_offset;
    return new_node_offset; 
}

void list_print(Arena *arena, uint32_t head_offset) {
    uint32_t current_offset = head_offset;
    
    printf("> VISUALISASI LINKED LIST\n");
    while (current_offset != 0) {
        Node *current_node = (Node*)arena_get(arena, current_offset);
        printf("[%d, Off:%u] -> ", current_node->value, current_offset);
        current_offset = current_node->next_offset;
    }
    printf("NULL\n");
}