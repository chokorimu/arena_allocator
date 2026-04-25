#include "arena.h"
#include <stdio.h>

int main() {
    Arena *arena = arena_init(64);
    printf("\nkondisi awal:");
    arena_dump(arena);

    uint32_t data1 = arena_alloc(arena, 32);
    printf("setelah alokasi 32 byte (Offset: %u):", data1);
    arena_dump(arena);

    arena_reset(arena);
    printf("setelah reset:");
    arena_dump(arena);

    return 0;
}