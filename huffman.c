
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "occurrence_heap.h"

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

	int occurenceArrSize = 0;
	Occurrence  **occurrences;

	while(lastIndex < filelen){

		if(bufferSize > filelen - lastIndex){
			bufferSize = filelen - lastIndex;
		}

		buffer = (char *)malloc((bufferSize) * sizeof(char)); // Enough memory for file + \0

		fseek(fileptr, 0, SEEK_CUR + lastIndex); 
		fread(buffer, bufferSize, 1, fileptr); // Read in the entire file
		
		for(int i = 0; i < bufferSize; i ++){
			occurenceArrSize = addOccurrence(occurrences, occurenceArrSize, buffer[i]);
			//printf("%c", buffer[i]);
		}

		lastIndex = lastIndex + bufferSize;

		free(buffer);

	}

	qsort(*occurrences, occurenceArrSize, 8, cmpfunc);

	printOccurrences(*occurrences, occurenceArrSize);

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

}


int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}