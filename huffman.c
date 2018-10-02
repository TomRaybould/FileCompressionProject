
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "huffman_tree.h"
#include "dynamic_list.h"

int addOccurrence(Occurrence **occurrences, int listSize, char c);
void printOccurrences(Occurrence *occurrences, int listSize);
void buildTree(Occurrence *occurrences, int listSize);
void readInFile(char *fileName);

int cmpfunc (const void *a, const void *b) {
   return (((Occurrence*)a)->numOfOccurrences - ((Occurrence*)b)->numOfOccurrences);
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

	int occurrenceArrSize = 0;
	Occurrence  **occurrences;

	while(lastIndex < filelen){

		if(bufferSize > filelen - lastIndex){
			bufferSize = filelen - lastIndex;
		}

		buffer = (char *)malloc((bufferSize) * sizeof(char)); // Enough memory for file + \0

		fseek(fileptr, 0, SEEK_CUR + lastIndex); 
		fread(buffer, bufferSize, 1, fileptr); // Read in the entire file
		
		for(int i = 0; i < bufferSize; i ++){
			occurrenceArrSize = addOccurrence(occurrences, occurrenceArrSize, buffer[i]);
			//printf("%c", buffer[i]);
		}

		lastIndex = lastIndex + bufferSize;

		free(buffer);

	}

	qsort(*occurrences, occurrenceArrSize, 8, cmpfunc);

	printOccurrences(*occurrences, occurrenceArrSize);

	buildTree(*occurrences, occurrenceArrSize);

	fclose(fileptr); // Close the file

}


int addOccurrence(Occurrence **occurrences, int listSize, char c){

	if(listSize == 0){
		*occurrences = (malloc(sizeof(Occurrence)));
		(*occurrences)[0].value = c;
		(*occurrences)[0].numOfOccurrences = 1;
		return 1;
	}

	else{
		//add one to number of occurrences if already in list 
		for(int i = 0; i < listSize; i++){
			Occurrence occurrence = (*occurrences)[i];
			if(occurrence.value == c){
				(*occurrences)[i].numOfOccurrences ++;
				return listSize;
			}
		}
		//else add new occurence
		Occurrence *newOccurrences = malloc(sizeof(Occurrence) * (listSize + 1));
		for(int i = 0; i < listSize; i++){
			newOccurrences[i] = (*occurrences)[i];
		}

		free(*occurrences);

		*occurrences = newOccurrences;

		(*occurrences)[listSize].value = c;
		(*occurrences)[listSize].numOfOccurrences = 1;

		return listSize + 1;

	}

}

void printOccurrences(Occurrence *occurrences, int listSize){

	for(int i = 0; i < listSize; i ++){
		printf("%c %d\n", occurrences[i].value, occurrences[i].numOfOccurrences);
	}

}

void buildTree(Occurrence *occurrences, int listSize){

	HuffmanNodeHeap **heap;

	//testing heap logic
	int size = 15;

	HuffmanNodeHeap *h = (HuffmanNodeHeap_create(size));

	heap = &h;

	for(char i = ('a' - 1) + size; i > ('a'- 1); i--){
		
		HuffmanNode *node = HuffmanNode_create(
			i,
			i,
			NULL,
			NULL);

		HuffmanNodeHeap_push(heap, node);

		HuffmanNodeHeap_print(*heap);

		printf("%s\n", "");
		
	}

	
	int heap_size = (*heap) -> size;

	while(heap_size > 0){

		heap_size = (*heap) -> size;
		
		if(heap_size < 2){
			//the tree is complete
			HuffmanNodeHeap_pop(heap);
			return;
		}
		else{
			//pick the 2 lowest from the heap
			HuffmanNode *sub_tree_1 = HuffmanNodeHeap_pop(heap);
			HuffmanNode *sub_tree_2 = HuffmanNodeHeap_pop(heap);

			//combine the to lowest by make a new parent
			int new_weight = sub_tree_1 -> weight + sub_tree_2 -> weight;
			HuffmanNode *new_parent_tree = HuffmanNode_create('p',
				new_weight,
				sub_tree_1,
				sub_tree_2);

			HuffmanNodeHeap_push(heap, new_parent_tree);

		}

	}

	/*
	while(node != NULL){
		HuffmanNode_destroy(node);
		node = HuffmanNodeHeap_pop(heap);
		HuffmanNodeHeap_print(*heap);
		printf("%s\n", "");
	}
	*/
	
}


int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}





