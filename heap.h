#ifndef HEAP_H
#define HEAP_H

struct Heap_
{
    int     size;
    void    (*destroy_data)(void *data);
    int     (*compare_data)(void *data_1, void *data_2);
    void    **data;
};

typedef struct Heap_ Heap;

int     Heap_init       (Heap *heap, int capacity, void (*destroy_data)(void *), int (*compare_data)(void *, void *));
void    Heap_push       (Heap *heap, void *data);
void    Heap_pop        (Heap *heap, void **data);
void    Heap_destroy    (Heap *heap);

#endif