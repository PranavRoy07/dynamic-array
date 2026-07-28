#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

/* da_init: allocate room for 4 ints on the heap. size=0, capacity=4 */
void da_init(DynamicArray *arr) {
    arr->data = malloc(4 * sizeof(int));
    if (arr->data == NULL) {
        fprintf(stderr, "da_init: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = 4;
}

/* da_push: add a value, doubling capacity via realloc when full.
   ALWAYS check realloc's return value before overwriting the old pointer -
   if realloc fails it returns NULL and the original block is still valid,
   so assigning straight into arr->data would leak that block. */
void da_push(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        int new_capacity = arr->capacity * 2;
        int *new_data = realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "da_push: realloc failed\n");
            exit(EXIT_FAILURE);
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
        printf("  [resize] capacity doubled to %d\n", new_capacity);
    }
    arr->data[arr->size] = value;
    arr->size++;
}

/* da_delete: remove the element at `index`, shifting everything after it
   left by one slot. memmove (not a hand-written loop) because the source
   and destination ranges overlap. */
void da_delete(DynamicArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "da_delete: index %d out of bounds\n", index);
        return;
    }
    int elements_after = arr->size - index - 1;
    if (elements_after > 0) {
        memmove(&arr->data[index], &arr->data[index + 1],
                elements_after * sizeof(int));
    }
    arr->size--;
}

/* da_free: release the heap block, then null out the struct fields so any
   accidental use-after-free crashes loudly instead of reading garbage. */
void da_free(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void da_print(DynamicArray *arr) {
    int i;

    printf("[");

    for (i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);

        if (i < arr->size - 1)
            printf(", ");
    }

    printf("] (size=%d, capacity=%d)\n", arr->size, arr->capacity);
}
