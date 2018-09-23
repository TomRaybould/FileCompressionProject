
#include <stdio.h>
#include <stdlib.h>

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

	while(lastIndex < filelen){

		if(bufferSize > filelen - lastIndex){
			bufferSize = filelen - lastIndex;
		}

		buffer = (char *)malloc((bufferSize) * sizeof(char)); // Enough memory for file + \0

		fseek(fileptr, 0, SEEK_CUR + lastIndex); 
		fread(buffer, bufferSize, 1, fileptr); // Read in the entire file
		
		for(int i = 0; i < bufferSize; i ++){
			printf("%c", buffer[i]);
		}

		lastIndex = lastIndex + bufferSize;

		free(buffer);

	}

	fclose(fileptr); // Close the file

}

int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}