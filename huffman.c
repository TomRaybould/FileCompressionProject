
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int addOccurence(Occurence **occurences, int listSize, char c);
void printOccurences(Occurence *occurences, int listSize);
void readInFile(char *fileName);

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
	Occurence  **occurences;

	while(lastIndex < filelen){

		if(bufferSize > filelen - lastIndex){
			bufferSize = filelen - lastIndex;
		}

		buffer = (char *)malloc((bufferSize) * sizeof(char)); // Enough memory for file + \0

		fseek(fileptr, 0, SEEK_CUR + lastIndex); 
		fread(buffer, bufferSize, 1, fileptr); // Read in the entire file
		
		for(int i = 0; i < bufferSize; i ++){
			occurenceArrSize = addOccurence(occurences, occurenceArrSize, buffer[i]);
			//printf("%c", buffer[i]);
		}

		lastIndex = lastIndex + bufferSize;

		free(buffer);

		printOccurences(*occurences, occurenceArrSize);

	}

	fclose(fileptr); // Close the file

}


int addOccurence(Occurence **occurences, int listSize, char c){

	if(listSize == 0){
		*occurences = (malloc(sizeof(Occurence)));
		(*occurences)[0].value = c;
		(*occurences)[0].numOfOccurences = 1;
		return 1;
	}

	else{
		//add one to number of occurences if already in list 
		for(int i = 0; i < listSize; i++){
			Occurence occurence = (*occurences)[i];
			if(occurence.value == c){
				occurence.numOfOccurences++;
				return listSize;
			}
		}
		//else add new occurence
		Occurence *newOccurences = malloc(sizeof(Occurence) * (listSize + 1));
		for(int i = 0; i < listSize; i++){
			newOccurences[i] = (*occurences)[i];
		}

		free(*occurences);

		*occurences = newOccurences;

		(*occurences)[listSize].value = c;
		(*occurences)[listSize].numOfOccurences = 1;

		return listSize + 1;

	}

}

void printOccurences(Occurence *occurences, int listSize){

	for(int i = 0; i < listSize; i ++){
		printf("%c %d\n", occurences[i].value, occurences[i].numOfOccurences);
	}

}


int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}