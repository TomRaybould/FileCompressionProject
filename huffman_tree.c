#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"

void sift_up	(HuffmanNodeHeap **heap, int position);
void sift_down	(HuffmanNodeHeap **heap, int position);

HuffmanNodeHeap* HuffmanNodeHeap_create(int size){	

	HuffmanNodeHeap *heap = malloc(sizeof(HuffmanNodeHeap));
	heap -> capacity = size;
	heap -> size = 0;
	heap -> data = malloc(sizeof(HuffmanNode) * size);
	
	return heap;
}

void HuffmanNodeHeap_push(HuffmanNodeHeap **heap, HuffmanNode node){
	HuffmanNodeHeap *h = *heap;

	HuffmanNode *node_pointer = HuffmanNode_create(node.value,
		node.weight,
		node.right,
		node.left);

	int curr_size = h -> size;

	((h -> data)[curr_size]) = node_pointer;

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

	HuffmanNode *root_node = &(*((h -> data)[0]));

	HuffmanNode *node = HuffmanNode_create(root_node -> value, 
		root_node -> weight, 
		root_node -> left,
		root_node -> right);

	//swap last node with first node
	HuffmanNode *last_node = &(*((h -> data)[curr_size - 1]));

	root_node -> value 	= last_node -> value;
	root_node -> weight = last_node -> weight;

	curr_size --;
	h -> size = curr_size;

	sift_down(heap, 0);

	return node;
	
}


void sift_up(HuffmanNodeHeap **heap, int position){
	if(position <= 0){
		return;
	}

	int parent_index = (position - 1) / 2;
	
	HuffmanNode **data = (*heap) -> data;  

	HuffmanNode *parent = &(*(data[parent_index]));
	HuffmanNode *curr 	= &(*(data[position]));

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

void sift_down(HuffmanNodeHeap **heap, int position){
	HuffmanNodeHeap *h = *heap;
	int heap_size = h -> size;

	if(position > heap_size){
		return;
	}

	int left_child_index = 	(position * 2) + 1;
	int right_child_index = (position * 2) + 2;

	HuffmanNode **data = (*heap) -> data;

	HuffmanNode *right_child = NULL;
	HuffmanNode *left_child  = NULL;
	HuffmanNode *curr_node   = &(*(data[position]));
	
	if(left_child_index <= heap_size){
		left_child = &(*(data[left_child_index]));
	}
	if(right_child_index <= heap_size){
		right_child = &(*(data[right_child_index]));
	}

	//cant sift any further
	if(left_child == NULL){
		return;
	}

	if(right_child == NULL ||
		left_child -> weight <= right_child -> weight){

		if(left_child -> weight < curr_node -> weight){

			char 	temp_val 	= curr_node -> value;
			int 	temp_weight = curr_node -> weight;

			curr_node -> value 	= left_child -> value;
			curr_node -> weight = left_child -> weight;

			left_child -> value  = temp_val;
			left_child -> weight = temp_weight;

			sift_down(heap, left_child_index);
		}
	}
	else{
		if(right_child -> weight < curr_node -> weight){

			char 	temp_val 	= curr_node -> value;
			int 	temp_weight = curr_node -> weight;

			curr_node -> value 	= right_child -> value;
			curr_node -> weight = right_child -> weight;

			right_child -> value  = temp_val;
			right_child -> weight = temp_weight;

			sift_down(heap, right_child_index);
		}
	}
}

void HuffmanNodeHeap_print(HuffmanNodeHeap *heap){

	int size = heap -> size;
	HuffmanNode **data = heap -> data; 

	for (int i = 0; i < size; i++){
		HuffmanNode node = *(data[i]);
		printf("Value: %c, Weight: %d\n", node.value, node.weight);
	}

}

//recursively build tree
HuffmanNode* HuffmanNode_create(char value, int weight, HuffmanNode *left, HuffmanNode *right){
	HuffmanNode *node = malloc(sizeof(HuffmanNode));
	node -> value 	= value;
	node -> weight 	= weight;

	if(left != NULL){
		HuffmanNode_create(left -> value, 
			left -> weight, 
			left -> left, 
			left -> right);
	}
	if(right != NULL){
		HuffmanNode_create(right -> value, 
			right -> weight, 
			right -> left, 
			right -> right);
	}

	return node;
}

//recursively destory tree from root
void HuffmanNode_destroy(HuffmanNode *node){
	
	if(node -> left != NULL){
		HuffmanNode_destroy(node -> left);
	}
	if(node -> right != NULL){
		HuffmanNode_destroy(node -> right);
	}

	free(node);
}

