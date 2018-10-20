#include <stdlib.h>
#include <printf.h>
#include "heap.h"

void sift_up	(Heap *heap, int position);
void sift_down	(Heap *heap, int curr_pos);

int  parent(int pos);
int  right_child(int pos);
int  left_child(int pos);

int Heap_init(Heap *heap, int capacity, void (*destroy_data)(void *), int (*compare_data)(void *, void *), void (*print_data)(void *)){

    void **data = malloc(sizeof(void *) * capacity);

    if(data == NULL){
        return -1;
    }

    heap -> data = data;
    heap -> size = 0;
    heap -> print_data = print_data;
    heap -> destroy_data = destroy_data;
    heap -> compare_data = compare_data;

    return 0;
}


void Heap_push(Heap *heap, void *data){

    int curr_size = heap -> size;

    (heap -> data)[curr_size] = data;

    heap -> size++;

    sift_up(heap, curr_size);

}


void sift_up(Heap *heap, int position){
    if(position <= 0){
        return;
    }

    int parent_index = parent(position);

    void **data = heap -> data;

    void *parent = data[parent_index];
    void *curr   = data[position];

    int comp = heap -> compare_data(parent, curr);

    if(comp > 0){
        void *temp = parent;
        data[parent_index] = curr;
        data[position] = temp;

        sift_up(heap, parent_index);
    }

}


void Heap_pop(Heap *heap, void **data){

    int curr_size = heap -> size;

    if(curr_size <= 0){
        *data = NULL;
        return;
    }

    *data = ((heap -> data)[0]);

    heap -> size--;

    if(heap -> size == 0){
        return;
    }

    (heap -> data)[0] = (heap -> data)[curr_size - 1];

    (heap -> data)[curr_size - 1] = NULL;

    sift_down(heap, 0);

}

void sift_down	(Heap *heap, int curr_pos){
    int heap_size = heap -> size;

    if(curr_pos >= heap_size){
        return;
    }

    int left_child_index    = left_child(curr_pos);
    int right_child_index   = right_child(curr_pos);

    void **data = heap -> data;

    void *right_child = NULL;
    void *left_child  = NULL;
    void *curr_node   = data[curr_pos];

    if(left_child_index < heap_size){
        left_child = data[left_child_index];
    }
    if(right_child_index < heap_size){
        right_child = data[right_child_index];
    }

    //cant sift any further
    if(left_child == NULL){
        return;
    }

    int (*compFun)(void *, void *) = heap -> compare_data;

    if(right_child == NULL ||
       compFun(right_child, left_child) > 0){

        if(compFun(curr_node, left_child) > 0){
            void *temp = left_child;
            data[left_child_index] = curr_node;
            data[curr_pos] = temp;
            sift_down(heap, left_child_index);
        }
    }
    else{
        if(compFun(curr_node, right_child) > 0){
            void *temp = right_child;
            data[right_child_index] = curr_node;
            data[curr_pos] = temp;
            sift_down(heap, right_child_index);
        }
    }

}

void Heap_print (Heap *heap){

    printf("Printing Heap... \n");

    int size = heap -> size;
    if(size < 1){
        return;
    }

    void **data = heap -> data;

    for(int i = 0; i < size; i ++){
        heap -> print_data(data[i]);
        printf("\n");
    }

}

int parent(int pos){
    return (pos - 1)/2;
}

int left_child(int pos){
    return (pos * 2) + 1;
}

int right_child(int pos){
    return (pos * 2) + 2;
}


