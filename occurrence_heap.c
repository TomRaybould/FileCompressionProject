#include <stdio.h>
#include <stdlib.h>
#include "occurrence_heap.h"

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


void sift_up(HuffmanNodeHeap *heap){
	//int curr_size = *()

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

