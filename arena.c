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
    printf("\n> ARENA DUMP (Size: %zu, Used: %zu) \n", arena->size, arena->offset);
    int cols = 64;
    printf("[");
    for (size_t i = 0; i < arena->size; i++) {
        if (i < arena->offset) {
            printf("+");
        } else {
            printf("-");
        }
        if (i == cols-1) {
            continue;
        } else if ((i + 1) % cols == 0) printf("\n");
    }
    printf("]");
    printf("\n\n");
}