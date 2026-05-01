#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *buffer;
    size_t size;
    size_t offset;
} Arena;

typedef struct {
    int value;
    uint32_t next_offset;
} Node;

typedef struct {
    uint32_t start_offset;
    size_t length;
} ArenaArray;

Arena* arena_init(size_t size);
uint32_t arena_alloc(Arena *arena, size_t size);
void* arena_get(Arena *arena, uint32_t offset);
void arena_reset(Arena *arena);
void arena_dump(Arena *arena);

uint32_t list_prepend(Arena *arena, uint32_t head_offset, int value);
void list_print(Arena *arena, uint32_t head_offset);

#endif