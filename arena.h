#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *buffer;
    size_t size;
    size_t offset;
} Arena;

Arena* arena_init(size_t size);
uint32_t arena_alloc(Arena *arena, size_t size);
void* arena_get(Arena *arena, uint32_t offset);
void arena_reset(Arena *arena);
void arena_dump(Arena *arena);

#endif