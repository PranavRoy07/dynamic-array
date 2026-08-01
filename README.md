# Dynamic Array in C

A custom implementation of a dynamic array (equivalent to Python's `list` or Java's `ArrayList`) built from scratch in C — using manual memory management with `malloc`, `realloc`, and `free`. Includes a companion memory demonstration showing the difference between stack and heap allocation.

Verified: **zero memory leaks** (Valgrind confirms 4 allocs, 4 frees).

---

## What this project demonstrates

| Concept | Implementation |
|---|---|
| Manual heap allocation | `malloc` / `realloc` / `free` — no garbage collection |
| Geometric resizing | Capacity doubles on overflow: 4 → 8 → 16 (O(1) amortized `push`) |
| `memmove` for safe element shifting | `da_delete` uses `memmove` — source and destination overlap when shifting elements left |
| Pointer nulling after `free` | `da_free` sets `data = NULL` after freeing — prevents use-after-free bugs |
| Stack vs heap memory | `memory_demo.c` shows address ranges, lifetime differences, and a caught use-after-free |
| Size vs capacity tracking | `size` = elements stored; `capacity` = allocated slots — always maintained in sync |

---

## Key implementation details

### `da_push` — amortized O(1) insert
When `size == capacity`, the array reallocates to `capacity * 2` using `realloc`. If `realloc` moves the block to a new address, it copies the contents automatically and frees the old block. `data` is updated to the new address.

### `da_delete` — safe element removal
Uses `memmove` (not `memcpy`) because shifting elements left creates overlapping source and destination regions — `memcpy` has undefined behaviour on overlapping regions; `memmove` does not.

### `da_free` — safe cleanup
```c
void da_free(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;   // prevents dangling pointer use after free
    arr->size = 0;
    arr->capacity = 0;
}
```

### `memory_demo.c` — stack vs heap
Demonstrates five memory concepts with printed output:
- Stack addresses vs heap addresses (different ranges)
- Heap memory persisting after function return (unlike stack)
- Use-after-free: GCC raises `-Wuse-after-free` on the demo lines — this is intentional, not a bug to silence

---

## Verified results

```
$ make build       # compiles cleanly, no warnings in dynamic_array.c
$ ./memory_demo    # stack vs heap demo runs and prints correctly
$ ./main           # pushes 10 values (resizes 4→8→16), deletes from middle and front, frees all

$ make valgrind
==== HEAP SUMMARY: in use at exit: 0 bytes in 0 blocks
==== total heap usage: 4 allocs, 4 frees, 4,208 bytes allocated
==== All heap blocks were freed -- no leaks are possible
==== ERROR SUMMARY: 0 errors from 0 contexts
```

---

## File structure

```
dynamic-array/
├── dynamic_array.h     — struct definition + function declarations
├── dynamic_array.c     — da_init, da_push, da_delete, da_free implementations
├── main.c              — demo: push 10 values, resize, delete, free
├── memory_demo.c       — stack vs heap address comparison + use-after-free demo
├── Makefile            — build, run, valgrind targets
└── README.md
```

---

## Running locally

### Linux / macOS
```bash
make build
./main
./memory_demo
make valgrind    # requires valgrind installed
```

### Windows (no local install)
Use **onlinegdb.com** with C selected. Add `dynamic_array.h`, `dynamic_array.c`, and `main.c` as a multi-file project. Enable the Valgrind memcheck option under run settings. For `memory_demo.c`, run as a separate single-file project.

Fallback: **replit.com** with a C repl — open the Shell tab and run `apt install valgrind` inside the disposable container.

---

## Tech stack

- C (C11)
- `malloc` / `realloc` / `free` / `memmove`
- Makefile build system
- Valgrind for memory leak verification
