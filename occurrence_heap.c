#include <stdio.h>
#include <stdlib.h>
#include "occurrence_heap.h"

void sift_up(HuffmanNodeHeap **heap, int position);

HuffmanNodeHeap* HuffmanNodeHeap_create(int size){	

	HuffmanNodeHeap *heap = malloc(sizeof(HuffmanNodeHeap));
	heap -> capacity = size;
	heap -> size = 0;
	heap -> data = malloc(sizeof(HuffmanNode) * size);
	
	return heap;
}

void HuffmanNodeHeap_push(HuffmanNodeHeap **heap, HuffmanNode node){
	HuffmanNodeHeap *h = *heap;

	int curr_size = h -> size;

	HuffmanNode *nodeInHeap = &((h -> data)[curr_size]);
	nodeInHeap -> value = node.value;
	nodeInHeap -> weight = node.weight;

	curr_size ++;
	h -> size = curr_size;
	sift_up(heap, curr_size - 1);	
}

HuffmanNode* HuffmanNodeHeap_pop (HuffmanNodeHeap **heap){
	
	HuffmanNodeHeap *h = *heap;
	int curr_size = h -> size;
	
	if(curr_size <= 0){
		return NULL;
	}

	HuffmanNode rootNode = (h -> data)[0];
	HuffmanNode *node = HuffmanNode_create(rootNode.value, rootNode.weight);

	printf("%d\n", curr_size);
	curr_size --;

	h -> size = curr_size;
	return node;
	
}


void sift_up(HuffmanNodeHeap **heap, int position){
	if(position <= 0){
		return;
	}

	int parent_index = (position - 1) / 2;
	
	HuffmanNode *data = (*(heap)) -> data;  

	HuffmanNode *parent = &(data[parent_index]);
	HuffmanNode *curr 	= &(data[position]);

	if(curr -> weight < parent -> weight){

		char 	temp_val 	= parent -> value;
		int 	temp_weight = parent -> weight;

		parent -> value  = curr -> value;
		parent -> weight = curr -> weight;
		curr   -> value  = temp_val;
		curr   -> weight = temp_weight;

		sift_up(heap, parent_index);

	}

}

void sift_down(){

}


void HuffmanNodeHeap_print(HuffmanNodeHeap *heap){

	int size = heap -> size;
	HuffmanNode *data = heap -> data; 

	for (int i = 0; i < size; i++){
		HuffmanNode node = data[i];
		printf("Value: %c, Weight: %d\n", node.value, node.weight);
	}

}

HuffmanNode* HuffmanNode_create(char value, int weight){
	HuffmanNode *node = malloc(sizeof(HuffmanNode));
	node -> value 	= value;
	node -> weight 	= weight;
	return node;
}

void HuffmanNode_destroy(HuffmanNode *node){
	free(node);
}

