
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "huffman_tree.h"
#include "dynamic_list.h"
#include "hashmap.h"

void 				addOccurrence		(DynamicList **list, char c);
void 				printOccurrences	(void **occurrences, int list_size);
HuffmanTreeNode* 	buildTree			(Occurrence **occurrences, int list_size, int total_chars);
HashMap*			buildHashMap		(HuffmanTreeNode *root, int size);
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

	int lastIndex = 0;


	DynamicList *dl = DynamicList_create(10);
	DynamicList **occ_list = &dl;

	int total_chars = 0;

	while(lastIndex < filelen){

		if(bufferSize > filelen - lastIndex){
			bufferSize = filelen - lastIndex;
		}

		buffer = (char *)malloc((bufferSize) * sizeof(char)); // Enough memory for file + \0

		fseek(fileptr, 0, SEEK_CUR + lastIndex); 
		fread(buffer, bufferSize, 1, fileptr); // Read in the entire file
		
		for(int i = 0; i < bufferSize; i ++){
			addOccurrence(occ_list, buffer[i]);
			total_chars++;
			//printf("%c", buffer[i]);
		}

		lastIndex = lastIndex + bufferSize;

		free(buffer);

	}

	DynamicList *l = *occ_list;

	DynamicList_trim(occ_list);

	qsort((l -> data), l -> size, (sizeof(void *)), cmpfunc);

	printOccurrences((l -> data), l -> size);

	buildTree((Occurrence**)(l -> data), l -> size, total_chars);

	fclose(fileptr); // Close the file

}

void addOccurrence(DynamicList **list, char c){
	DynamicList *l = *list;
	int list_size = l -> size;
	Occurrence **data =((Occurrence **) (l -> data));
	
	//add one to number of occurrences if already in list 
	for(int i = 0; i < list_size; i++){
		Occurrence *occurrence = data[i];
		if(occurrence -> value == c){
			occurrence -> numOfOccurrences++;
			return;
		}
	}
	//else add new occurence
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
			int new_weight = sub_tree_1 -> weight + sub_tree_2 -> weight;
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

HashMap* buildHashMap(HuffmanTreeNode *root, int size){

	HashMap *map = HashMap_create(size);

	while()

}

void resMapPop(HashMap **map, HuffmanTreeNode *node, int code_bit_length, unsigned int code){
	if(node == NULL){
		return;
	}

	code = 

	resMapPop(node -> left	, 0, NULL, 0);
	resMapPop(node -> right	, 0, NULL, 1);
}


int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}





