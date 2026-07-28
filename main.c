#include <stdio.h>
#include "dynamic_array.h"

int main(void)
{
    DynamicArray arr;
    int i;

    da_init(&arr);

    printf("=== Pushing 10 values (watch capacity double: 4 -> 8 -> 16) ===\n");

    for (i = 1; i <= 10; i++) {
        da_push(&arr, i * 10);
    }

    da_print(&arr);

    printf("\n=== Deleting index 3 (memmove shifts everything after it left) ===\n");
    da_delete(&arr, 3);
    da_print(&arr);

    printf("\n=== Deleting index 0 ===\n");
    da_delete(&arr, 0);
    da_print(&arr);

    printf("\n=== Attempting an out-of-bounds delete (should print an error, not crash) ===\n");
    da_delete(&arr, 99);

    printf("\n=== Freeing the array ===\n");
    da_free(&arr);

    printf("arr.data is now %p\n", (void *)arr.data);

    return 0;
}
