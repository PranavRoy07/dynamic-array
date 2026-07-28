#include <stdio.h>
#include <stdlib.h>

/* Run this FIRST, before touching dynamic_array.c.
   It's a live demonstration of stack vs heap memory - the mental model
   everything else in this phase depends on. */
int main(void) {
    printf("=== Stack vs Heap: 5 examples ===\n\n");

    /* 1. A local variable lives on the stack. It's created and destroyed
          automatically when main() returns - no cleanup needed. */
    int stack_num = 42;
    printf("1. Stack int  -> value=%d  address=%p\n", stack_num, (void *)&stack_num);

    /* 2. malloc asks the OS/heap allocator for space YOU must manage. */
    int *heap_num = malloc(sizeof(int));
    if (heap_num == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }
    *heap_num = 42;
    printf("2. Heap int   -> value=%d  address=%p\n", *heap_num, (void *)heap_num);

    /* 3. Compare the two addresses - they come from very different regions
          of the process's memory space (stack grows down from high
          addresses, heap grows up from low addresses on most systems). */
    printf("3. Stack address %p vs heap address %p - different memory regions\n",
           (void *)&stack_num, (void *)heap_num);

    /* 4. free() gives the memory back. The pointer VARIABLE still holds the
          old numeric address, but the memory itself is no longer ours. */
    free(heap_num);
    printf("4. Freed heap_num. Pointer still reads %p, but that memory is gone.\n",
           (void *)heap_num);

    /* 5. Reading through a freed pointer is undefined behaviour: it might
          print the old value, garbage, or crash. Do not do this in real
          code - this line exists purely so you SEE why it's dangerous. */
    printf("5. Reading freed memory (undefined behaviour, never do this for real): %d\n",
           *heap_num);

    /* The safe pattern going forward: null the pointer immediately after
       freeing, so any future use crashes instead of silently corrupting
       something. */
    heap_num = NULL;

    printf("\nStack: automatic, scoped to the function, no cleanup needed.\n");
    printf("Heap:  manual, lives until YOU free it, use-after-free is a real bug class.\n");

    return 0;
}