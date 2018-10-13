
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "huffman_tree.h"
#include "dynamic_list.h"
#include "hashmap.h"

void 				addOccurrence		(DynamicList *list, char c);
void 				printOccurrences	(void **occurrences, int list_size);
HuffmanTreeNode* 	buildTree			(Occurrence **occurrences, int list_size, int total_chars);
HashMap*			buildHashMap		(HuffmanTreeNode *root, int size);
void 				recsMapPop			(HashMap **map, HuffmanTreeNode *node, int code_bit_length, unsigned int code);
void 				readInFile			(char *fileName);

int cmpfunc (const void *a, const void *b) {
	Occurrence **occ_ap = (Occurrence**)(a);
	Occurrence **occ_bp = (Occurrence**)(b);
	Occurrence *occ_a = *occ_ap;
	Occurrence *occ_b = *occ_bp;
   return (occ_a -> numOfOccurrences - occ_b ->numOfOccurrences);
}

/**
Reads in the file using a buffer and spits out a char array representing the files content
*/
void readInFile(char *fileName){
	FILE *fileptr;
	char *buffer;
	long filelen;
	long bufferSize = 2048;

	//printf("%s\n", fileName);
	fileptr = fopen(fileName, "rb");  	// Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);      	// Jump to the end of the file
	filelen = ftell(fileptr);           // Get the current byte offset in the file
	rewind(fileptr);                    // Jump back to the beginning of the file

	long lastIndex = 0;

	DynamicList *occ_list = malloc(sizeof(DynamicList));


	DynamicList_init(occ_list, 10, destroyOccurrence);

	int total_chars = 0;

	while(lastIndex < filelen){

		if(bufferSize > filelen - lastIndex){
			bufferSize = filelen - lastIndex;
		}

		buffer = (char *)malloc((bufferSize) * sizeof(char)); // Enough memory for file + \0

		fseek(fileptr, 0, (int) (SEEK_CUR + lastIndex));
		fread(buffer, (size_t) bufferSize, 1, fileptr); // Read in the entire file
		
		for(int i = 0; i < bufferSize; i ++){
			addOccurrence(occ_list, buffer[i]);
			total_chars++;
			//printf("%c", buffer[i]);
		}

		lastIndex = lastIndex + bufferSize;

		free(buffer);

	}

	DynamicList_trim(occ_list);

	qsort((occ_list -> data), (size_t) occ_list -> size, (sizeof(void *)), cmpfunc);

	printOccurrences((occ_list -> data), occ_list -> size);

	buildTree((Occurrence**)(occ_list -> data), occ_list -> size, total_chars);

	DynamicList_destroy(occ_list);

	fclose(fileptr); // Close the file

}

void addOccurrence(DynamicList *list, char c){
	int list_size = list -> size;
	Occurrence **data =((Occurrence **) (list -> data));
	
	//add one to number of occurrences if already in list 
	for(int i = 0; i < list_size; i++){
		Occurrence *occurrence = data[i];
		if(occurrence -> value == c){
			occurrence -> numOfOccurrences++;
			return;
		}
	}
	//else add new occurrence
	Occurrence *occurrence = malloc(sizeof(Occurrence));
	occurrence -> value = c;
	occurrence -> numOfOccurrences = 1;

	DynamicList_add(list, occurrence);
}

void printOccurrences(void **occurrences, int list_size){
	for(int i = 0; i < list_size; i ++){
		Occurrence *occurrence = (Occurrence(*))occurrences[i];
		printf("%c %d\n", occurrence->value, occurrence -> numOfOccurrences);
	}

}

HuffmanTreeNode* buildTree(Occurrence **occurrences, int list_size, int total_chars){

	HuffmanNodeHeap **heap;

	//testing heap logic
	int size = 15;

	HuffmanNodeHeap *h = (HuffmanNodeHeap_create(size));

	heap = &h;

	for(int i = 0; i < list_size; i++){
		
		Occurrence *occurrence = occurrences[i];

		double weight = (double) occurrence -> numOfOccurrences / (double) total_chars;

		HuffmanTreeNode *node = HuffmanTreeNode_create(
			occurrence -> value,
			weight,
			NULL,
			NULL);

		HuffmanNodeHeap_push(heap, node);
		
	}

	printf("%s\n", "");

	HuffmanNodeHeap_print(*heap);

	int heap_size = (*heap) -> size;

	while(heap_size > 0){

		heap_size = (*heap) -> size;
		
		if(heap_size < 2){
			//the tree is complete
			return HuffmanNodeHeap_pop(heap);
		}
		else{
			//pick the 2 lowest from the heap
			HuffmanTreeNode *sub_tree_1 = HuffmanNodeHeap_pop(heap);
			HuffmanTreeNode *sub_tree_2 = HuffmanNodeHeap_pop(heap);

			//combine the to lowest by make a new parent
            double new_weight = sub_tree_1 -> weight + sub_tree_2 -> weight;
			HuffmanTreeNode *new_parent_tree = HuffmanTreeNode_create('p',
				new_weight,
				sub_tree_1,
				sub_tree_2);

			HuffmanNodeHeap_push(heap, new_parent_tree);

		}

	}

	return HuffmanNodeHeap_pop(heap);

	/*
	while(node != NULL){
		HuffmanTreeNode_destroy(node);
		node = HuffmanNodeHeap_pop(heap);
		HuffmanNodeHeap_print(*heap);
		printf("%s\n", "");
	}
	*/
	
}

void recsMapPop(HashMap **map, HuffmanTreeNode *node, int code_bit_length, unsigned int code){
	if(node == NULL){
		return;
	}

	//only for leaf nodes
	if(code_bit_length > 0 && node -> right == NULL && node -> left == NULL){
		int *data = malloc(sizeof(int));
		HashMap_put(map, node -> value, data, code_bit_length);
	}

	code = code << 1;
	code_bit_length++;

	//adds one to the code for the right side
	recsMapPop(map, node -> right, code_bit_length, code | 0x0001);
	//adds zero to the code fo the left side
	recsMapPop(map, node -> left, code_bit_length, code);
}

HashMap* buildHashMap(HuffmanTreeNode *root, int size){

	HashMap *map = HashMap_create(size);	

	recsMapPop(&map, root, 0, 0x0000);

	return map;

}

int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}





