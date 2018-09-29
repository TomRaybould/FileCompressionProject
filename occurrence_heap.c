#include <stdio.h>
#include <stdlib.h>
#include "occurrence_heap.h"

HuffmanNodeHeap* HuffmanNodeHeap_create(int size){	

	HuffmanNodeHeap *heap = malloc(sizeof(HuffmanNodeHeap));
	heap -> capacity = size;
	int curr_size = 0;
	heap -> size = &curr_size;
	heap -> data = malloc(sizeof(HuffmanNode) * size);
	
	return heap;
}


void HuffmanNodeHeap_push(HuffmanNodeHeap *heap, HuffmanNode node){
	int curr_size = *(heap -> size);
	(heap -> data)[curr_size] = node;
	curr_size ++;
	(heap -> size) = &curr_size;
}


HuffmanNode HuffmanNodeHeap_pop();


void HuffmanNodeHeap_print(HuffmanNodeHeap *heap){

	int size = *(heap -> size);
	HuffmanNode *data = heap -> data; 

	for (int i = 0; i < size; i++){
		HuffmanNode node = data[i];
		printf("Value: %c, Weight: %d\n", node.value, node.weight);
	}

}