#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

void da_init(DynamicArray *arr);
void da_push(DynamicArray *arr, int value);
void da_delete(DynamicArray *arr, int index);
void da_free(DynamicArray *arr);
void da_print(DynamicArray *arr);

#endif