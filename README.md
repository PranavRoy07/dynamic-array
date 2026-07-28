# Phase 1 — Custom Dynamic Array in C

## What this actually is, in plain terms
A Python `list` or Java `ArrayList` looks like magic — you just `.append()` and it
grows forever. Under the hood, it's not magic: it's a block of memory that gets
copied into a *bigger* block of memory whenever it runs out of room. This project
makes you build that mechanism by hand in C, where nothing is automatic and every
mistake shows up as a crash or a memory leak instead of being hidden from you.

Two files matter more than the others:

- **`memory_demo.c`** — five small experiments showing the difference between
  **stack** memory (automatic, cleaned up when a function returns) and **heap**
  memory (manual — you ask for it with `malloc`, you give it back with `free`,
  and nothing stops you from reading it after you've freed it, which is a real
  and dangerous bug). Run this one first, before you look at the array code.
- **`dynamic_array.c` / `.h`** — the actual `DynamicArray` struct: `da_init`,
  `da_push` (doubles capacity via `realloc` when full), `da_delete` (uses
  `memmove` because shifting elements left overlaps the source and destination),
  and `da_free` (frees the block, then nulls the pointer so nothing can use it
  by accident afterward).
- **`main.c`** — pushes 10 values (you'll see it resize 4 → 8 → 16), deletes
  from the middle and the front, tries an out-of-bounds delete safely, then
  frees everything.

## Verified results (I ran these myself before handing this to you)
```
$ make build          # compiles cleanly, no warnings in dynamic_array.c
$ ./memory_demo        # runs, shows stack vs heap addresses, and the use-after-free line
$ ./main                # pushes, resizes 4→8→16, deletes, frees
$ make valgrind
==== HEAP SUMMARY: in use at exit: 0 bytes in 0 blocks
==== total heap usage: 4 allocs, 4 frees, 4,208 bytes allocated
==== All heap blocks were freed -- no leaks are possible
==== ERROR SUMMARY: 0 errors from 0 contexts
```
Zero leaks. That's the phase's exit criterion, met.

One honest note: GCC itself flags `memory_demo.c` with a `-Wuse-after-free`
warning on lines 33 and 39. That's not a bug to fix — it's the compiler
literally proving the point the demo exists to make. Don't silence it.

## Running this on Windows with no installs (web-only)
Valgrind does not run natively on Windows, and the roadmap wants zero
local installs, so use a browser-based Linux environment instead of your
own machine:

1. Go to **onlinegdb.com**, choose **C** as the language.
2. Paste in `dynamic_array.h`, `dynamic_array.c`, and `main.c` as separate
   files in the project view (OnlineGDB supports multi-file C projects).
3. Under the debug/run options there's a **Valgrind memcheck** option for C —
   turn it on and run. You'll see the same "no leaks possible" summary shown
   above.
4. For `memory_demo.c`, just run it as its own single-file project — no
   Valgrind needed there, you're reading the printed output, not checking leaks.

If OnlineGDB's Valgrind option is ever unavailable, **replit.com** with a C
repl and a `shell` tab where you can `apt install valgrind` yourself is the
fallback — replit's shell lets you install packages inside your own
disposable container, no admin rights on your Windows machine needed either way.

## The mentorship challenge — do this part yourself
The roadmap is explicit: draw the pointer diagram *before* you trust this
code. Don't skip it just because the code already works. Sketch:
- a box labeled `arr` on the stack, holding `data` (a pointer), `size`, `capacity`
- an arrow from `data` to a separate heap block holding the actual ints
- what happens to that arrow when `realloc` decides to move the block:
  the heap block gets copied to a new address, the old address becomes
  invalid, and `data` gets repointed to the new address

If you can't draw that from memory after reading `dynamic_array.c`, reread
`da_push` until you can — that diagram is also the mental model for how
Java's `ArrayList` and Python's `list` work internally, and interviewers
will ask you to draw exactly this.
