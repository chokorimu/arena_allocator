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

    printf("alokasi array 5 int:");
    uint32_t arr_offset = arena_alloc(arena, 5 * sizeof(int));
    int *arr = (int*)arena_get(arena, arr_offset);
    for(int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
    }
    arena_dump(arena);

    printf("alokasi linked list 3 node:\n");
    uint32_t head = 0;
    head = list_prepend(arena, head, 100);
    head = list_prepend(arena, head, 200);
    head = list_prepend(arena, head, 300);
    list_print(arena, head);
    arena_dump(arena);

    arena_reset(arena);
    printf("setelah reset:");
    arena_dump(arena);
    
    return 0;
}