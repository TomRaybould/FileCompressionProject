
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "huffman_tree.h"
#include "dynamic_list.h"
#include "bitree.h"
#include "heap.h"
#include "hashmap.h"
#include "bit_ops.h"

HashMap*			buildHashMap		(BiTree *tree);
void 				recsMapPop			(HashMap *map, BiTreeNode *node,unsigned int code_bit_length, unsigned int code);
long 				read_in_file		(char *file_name, unsigned char **file_contents);
void 				scale_freqs			(int *freqs);
FILE*               write_to_file 		(char *filename, unsigned char* compressed_data, int total_bytes);
void	 			build_tree          (const int *freqs, BiTree** tree);
void 				print_int_as_bi		(const int num);
void 				decompress_file		(char *file_name);
void 				print_char_arr		(unsigned char *char_arr, int length);

//decompression
void 				read_in_compressed_file	(char *filename);
void 				parse_compressed_freqs	(unsigned char* buffer, int* freqs);
void 				printBits				(char * data, size_t size_of);

int CHAR_MAX = 255;

int cmpfunc (const void *a, const void *b) {
	Occurrence **occ_ap = (Occurrence**)(a);
	Occurrence **occ_bp = (Occurrence**)(b);
	Occurrence *occ_a = *occ_ap;
	Occurrence *occ_b = *occ_bp;
   return (occ_a -> weight - occ_b ->weight);
}

/*
	Reads the file in to the file_contents pointer to arr and returns
	the length of the file in bits.
*/
	
long read_in_file(char *fileName, unsigned char **file_contents){

	FILE *file;
	unsigned char *buffer;
	long file_len;

	printf("%s\n", fileName);
	file = fopen(fileName, "rb");  	// Open the file in binary mode
	fseek(file, 0, SEEK_END);      	// Jump to the end of the file
	file_len = ftell(file);     	// Get the current byte offset in the file
	rewind(file);                	// Jump back to the beginning of the file

	long lastIndex = 0;

	buffer = (unsigned char *)malloc((file_len) * sizeof(unsigned char)); // Enough memory for file + \0


	fseek(file, 0, (int) (SEEK_CUR + lastIndex));
	fread(buffer, (size_t) file_len, 1, file); // Read in the entire file

	unsigned char *copied_data = (unsigned char *)malloc((file_len) * sizeof(unsigned char)); // Enough memory for file + \0

	for(int i = 0; i < file_len; i ++){
		unsigned char c = buffer[i];
		copied_data[i] = c;
	}

	free(buffer);
	fclose(file);

	*file_contents = copied_data;

	return file_len;
}


/**
Reads in the file using a buffer and spits out a char array representing the files content
*/
void compress(char *file_name){
	
	unsigned char **file_contents; 

	long file_len = read_in_file(file_name, file_contents);

	unsigned char *buffer = *file_contents;

	print_char_arr(buffer, (int) file_len);

	int freqs[CHAR_MAX + 1];

	for(int i = 0; i < CHAR_MAX +1; i++){
		freqs[i] = 0;
	}

	int total_chars = 0;
	for(int i = 0; i < file_len; i ++){
		unsigned char c = buffer[i];
		freqs[c]++;
	    total_chars++;
	}

	scale_freqs(freqs);

	BiTree *tree = malloc(sizeof(BiTree));

	build_tree(freqs, &tree);

	HashMap *map = buildHashMap(tree);

	HashMap_print(map);

	int header_size = sizeof(int) + (CHAR_MAX + 1);

	unsigned char *compressed = malloc((size_t) header_size);

	memcpy(compressed, &total_chars, sizeof(int));

	for(int i = 0; i <= CHAR_MAX; i++){
		compressed[sizeof(int) + i] = (unsigned char) freqs[i];
	}

	unsigned int input_pos 	= 0;
	unsigned int output_pos = (unsigned int) (header_size * 8);

    printf("Compression: \n");
	for(input_pos = 0; input_pos < total_chars; input_pos++){

		HuffmanMapData *huffmanMapData;

		HashMap_get(map, buffer[input_pos], (void **) &huffmanMapData);

		for(int i = 0; i < huffmanMapData -> bit_length; i++){
			printf("bit_length %d\n", huffmanMapData -> bit_length);
			if(output_pos % 8 == 0){
				compressed = realloc(compressed, (output_pos / 8) + 1);
			}

			int int_size = sizeof(unsigned int);

			int tar_bit_idx  = (sizeof(int) * 8);
			tar_bit_idx = tar_bit_idx - ((huffmanMapData -> bit_length) - i);
			//printf("huffmanMapData -> code %d\n", huffmanMapData -> code);
            //printf("tar_bit_id %d\n", tar_bit_idx);
			int bit = bit_get((unsigned char *) &(huffmanMapData -> code), tar_bit_idx);
			//printf("bit %d\n", bit);
			bit_set(compressed, output_pos, bit);

			output_pos++;
		}

	}

	print_char_arr(compressed, (output_pos / 8 + 1));

    printf("\n");
	write_to_file(NULL, compressed, (output_pos / 8 + 1));

	free(buffer); // Close the file

}

void scale_freqs(int *freqs){

	//find max value
	int max_freq = CHAR_MAX;
	for(int i = 0; i <= CHAR_MAX; i++){
		int freq = freqs[i];
		if(freq > max_freq){
			max_freq = freq;
		}
	}

	for(int i = 0; i <= CHAR_MAX; i++){
		int freq = freqs[i];

		//scale to 0 - 255 value
		int scaled = (int)((double)freq / ((double)max_freq / (double)CHAR_MAX));

		if(scaled == 0 && freq > 0){
			scaled = 1;
		}

		freqs[i] = scaled;
	}
}


int comp_occ(void *o1, void *o2){

	Occurrence *occ1 = (Occurrence *)o1;
	Occurrence *occ2 = (Occurrence *)o2;

	int weight1 = occ1 -> weight;
	int weight2 = occ2 -> weight;

	if(weight1 == weight2){
        return 0;
	}
	if(weight1 > weight2){
        return 1;
	}
	else{
        return -1;
	}

}


int tree_comp(void *t1, void *t2){

    BiTree *tree_1 = (BiTree *) t1;
    BiTree *tree_2 = (BiTree *) t2;

    return comp_occ(tree_1 -> root -> data, tree_2 -> root -> data);

}


void build_tree(const int *freqs, BiTree **tree){

    Heap *heap = malloc(sizeof(Heap));

    Heap_init(heap, CHAR_MAX + 1, BiTree_destroy, tree_comp, (void (*)(void *)) BiTree_level_order_print);

    for(unsigned int c = 0; c <= 255; c++) {

    	if(freqs[c] == 0){
			continue;
    	}

    	Occurrence *occurrence = malloc(sizeof(Occurrence));

    	occurrence -> value  = (unsigned char) c;
    	occurrence -> weight = freqs[c];

    	print_occurrence(occurrence);
    	printf("\n");

        BiTree *temp_tree = malloc(sizeof(BiTree));
        BiTree_init(temp_tree, destroy_occurrence, print_occurrence);

        BiTree_ins_left(temp_tree, NULL, occurrence);

        Heap_push(heap, temp_tree);

    }

    printf("%s", "\n");
	//Heap_print(heap);
	printf("\n");

	while(heap -> size > 1){
		BiTree *tree1, *tree2;

		Heap_pop(heap, (void **) &tree1);
        Occurrence *occ1 = tree1 -> root -> data;
        //print_occurrence(occ1);
        //printf("\n");

        //Heap_print(heap);
        //printf("\n");

        Heap_pop(heap, (void **) &tree2);
        Occurrence *occ2 = tree2 -> root -> data;
		//print_occurrence(occ2);
        //printf("\n");

		//Heap_print(heap);
        //printf("\n");

		Occurrence *occ = malloc(sizeof(Occurrence));

		occ -> weight = occ1 -> weight + occ2 -> weight;
		occ -> value = 'x';

		BiTree *merged = malloc(sizeof(BiTree));

		BiTree_merge(merged, occ, tree1, tree2);

		Heap_push(heap, merged);
        //Heap_print(heap);

	}

	Heap_pop(heap, (void **) tree);

	BiTree_level_order_print(*tree);

}


void recsMapPop(HashMap *map, BiTreeNode *node, unsigned int code_bit_length, unsigned int code){
	if(node == NULL){
		return;
	}

	//only for leaf nodes
	if(code_bit_length > 0 && node -> right == NULL && node -> left == NULL){

        printf("code %d\n", code);
		HuffmanMapData *data    = malloc(sizeof(HuffmanMapData));
		data -> code	        = htonl(code);
		data -> bit_length      = code_bit_length;

		Occurrence *occurrence = (Occurrence*) node -> data;

		printf("key: %c, code: %d, bit_length: %d \n", occurrence -> value,data -> code, data -> bit_length);

		HashMap_put(map, occurrence -> value, data);
	}
	else{
	    printf("bit length: %d\n", code_bit_length);
	}

	code = code << 1;

	//adds one to the code for the right side
	recsMapPop(map, node -> right, code_bit_length + 1, (code | 0x0001));
	//adds zero to the code fo the left side
	recsMapPop(map, node -> left, code_bit_length + 1, code);
}

void free_data(void *data){
    free(data);
}

void HuffmanMapData_print(void* data){
	HuffmanMapData *huffmanMapData = data;
	printf("%u, ", huffmanMapData -> code);
	printf("%u", huffmanMapData -> bit_length);
}

HashMap* buildHashMap(BiTree *tree){

    BiTree_level_order_print(tree);

    void (*destroy_data)(void*) = free_data;

	HashMap *map = HashMap_create(255, destroy_data, HuffmanMapData_print);

	recsMapPop(map, tree -> root, 0, 0x0000);

	HashMap_print(map);

	return map;

}


FILE* write_to_file(char *filename, unsigned char* compressed_data, int total_bytes){

	FILE * fp;

	fp = fopen ("compressed.bin","wb");

	fwrite(compressed_data, sizeof(unsigned char), total_bytes, fp);

	/* close the file*/
	fclose (fp);
	return 0;

}


void decompress_file(char *file_name){

	unsigned char **file_contents; 

	long file_len = read_in_file(file_name, file_contents);

	printf("%ld\n", file_len);

	unsigned char *buffer = *file_contents;

	int original_file_length = *((int*) buffer);

	print_char_arr(buffer, (int)file_len);

	int freqs[CHAR_MAX + 1];

	parse_compressed_freqs(buffer, freqs);

	BiTree *tree = malloc(sizeof(BiTree));

	build_tree(freqs, &tree);

	int header_size = sizeof(int) + CHAR_MAX + 1;

	BiTreeNode *curr_node = tree -> root;

	unsigned int processed_bytes = 0;
	unsigned char uncompressed_data[original_file_length];

	printf("og file size%d\n", original_file_length);

	for(unsigned int i = header_size; i < file_len; i++){
		if(processed_bytes == original_file_length){
			break;
		}
		for(int j = 0; j < 8; j++){

			if(curr_node -> left == NULL && curr_node -> right == NULL){
				Occurrence *occurrence = (Occurrence*) curr_node -> data;
				uncompressed_data[processed_bytes] = occurrence -> value;
				processed_bytes ++;
				if(processed_bytes == original_file_length){
					break;
				}
				curr_node = tree -> root;
				print_occurrence(occurrence);
				printf("%s\n", "");
			}

			int bit = bit_get(buffer, (8 * i) + j);
			printf(" bit  %d\n", bit);
			
			if(bit){
				curr_node = curr_node -> right;
			}
			else{
				curr_node = curr_node -> left;
			}

		}
	}

	print_char_arr(uncompressed_data, original_file_length);
}

void parse_compressed_freqs(unsigned char* buffer, int* freqs){
	//offsetting the int storing the total bytes at beginning of file
	int start_offset = 4;

	for(int i = 0; i < CHAR_MAX + 1; i++){
		freqs[i] = buffer[start_offset + i];
	}

	scale_freqs(freqs);

}

void printBits(char * data, size_t size_of){
	int numOfBits = size_of * 8;	

	int currentByte = 0;
	for(int i = 0; i < numOfBits; i++){
		unsigned int byteIndex = i / 8;

		//add space inbetween btyes
		if(currentByte != byteIndex){
			currentByte = byteIndex;
			printf("%c", ' ');
		}

		// 0000 0001
		// substracting 7 because "1" is in the 7th index 
		unsigned int bitIndex = 7 - (i % 8);

		unsigned char mask = 0x01;
		
		mask = mask << (bitIndex);

		unsigned int isBitOne = (mask & data[byteIndex]);

		printf("%d", isBitOne);

	}

	printf("\n");

}


void print_int_as_bi(const int num){

	for (int j = 0; j < 32; ++j) {
		if(j % 4 == 0 && j != 0){
			printf(" ");
		}
		printf("%d", bit_get((const unsigned char *) &num, j));
	}

	printf("\n");
}

void print_char_arr(unsigned char *char_arr, int length){
	for(int i = 0; i < length; i++){
		printf("%c", char_arr[i]);
	}
	printf("\n");
}

int main (int argc, char *argv[]){
	printf("%s\n", argv[1]);
	compress(argv[1]);
	printf("\n");
	decompress_file("compressed.bin");
	return -1;

}





