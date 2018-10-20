
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "huffman_tree.h"
#include "dynamic_list.h"
#include "bitree.h"
#include "heap.h"
#include "hashmap.h"

void 				addOccurrence		(DynamicList *list, unsigned char c);
void 				printOccurrences	(void **occurrences, int list_size);
HashMap*			buildHashMap		(HuffmanTreeNode *root, int size);
void 				recsMapPop			(HashMap *map, HuffmanTreeNode *node, int code_bit_length, unsigned int code);
void 				readInFile			(char *fileName);
BiTree* 			build_tree          (DynamicList *occ_list);

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

	for(int i = 0; i < occ_list -> size; i ++){
		void **data = occ_list -> data;
		Occurrence *occurrence = (Occurrence *) data[i];
		double weight = occurrence -> numOfOccurrences / (double)total_chars;
		occurrence -> weight = weight;
	}

	printOccurrences((occ_list -> data), occ_list -> size);

	//buildTree((Occurrence**)(occ_list -> data), occ_list -> size, total_chars);

	build_tree(occ_list);

	//DynamicList_destroy(occ_list);

	fclose(fileptr); // Close the file

}

void addOccurrence(DynamicList *list, unsigned char c){
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

int comp_occ(void *o1, void *o2){

	Occurrence *occ1 = (Occurrence *)o1;
	Occurrence *occ2 = (Occurrence *)o2;

	return (int) (occ1 -> weight - occ2 -> weight);

}


int tree_comp(void *t1, void *t2){

    BiTree *tree_1 = (BiTree *) t1;
    BiTree *tree_2 = (BiTree *) t2;

    return comp_occ(tree_1 -> root -> data, tree_2 -> root -> data);

}

void print_heap(Heap *heap){
    int size = heap -> size;
    void **data = heap -> data;

    for(int i = 0; i < size; i++){
        BiTree *tree = data[i];
        BiTreeNode *treeNode = tree -> root;
        Occurrence *occ = treeNode -> data;
        printf("value: %c weight: %lf \n", occ -> value, occ -> weight);
    }

}


BiTree* build_tree(DynamicList *occ_list){

    int list_size = occ_list -> size;
    void **data = occ_list -> data;

    Heap *heap = malloc(sizeof(Heap));

    Heap_init(heap, list_size, BiTree_destroy, tree_comp);

    for(int i = 0; i < list_size; i++) {

        BiTree *tree = malloc(sizeof(BiTree));
        BiTree_init(tree, destroyOccurrence);

        BiTree_ins_left(tree, NULL, data[i]);

        Heap_push(heap, tree);

        printf("%s", "\n");
        print_heap(heap);

    }

	while(heap -> size > 0){

		BiTree *tree1, *tree2;

		Heap_pop(heap, (void **) &tree1);
		Heap_pop(heap, (void **) &tree2);

		Occurrence *occ1 = tree1 -> root -> data;
		Occurrence *occ2 = tree2 -> root -> data;

		Occurrence *occ = malloc(sizeof(Occurrence));

		occ -> weight = occ1 -> weight + occ2 -> weight;

		BiTree *merged = malloc(sizeof(BiTree));

		BiTree_merge(merged, occ, tree1, tree2);

		Heap_push(heap, merged);

	}

	void *result;

	Heap_pop(heap, &result);

	return result;
}


void recsMapPop(HashMap *map, HuffmanTreeNode *node, int code_bit_length, unsigned int code){
	if(node == NULL){
		return;
	}

	//only for leaf nodes
	if(code_bit_length > 0 && node -> right == NULL && node -> left == NULL){
		int *data = malloc(sizeof(int));
		HashMap_put(map, node -> value, data);
	}

	code = code << 1;
	code_bit_length++;

	//adds one to the code for the right side
	recsMapPop(map, node -> right, code_bit_length, code | 0x0001);
	//adds zero to the code fo the left side
	recsMapPop(map, node -> left, code_bit_length, code);
}

void free_data(void *data){
    free(data);
}

HashMap* buildHashMap(HuffmanTreeNode *root, int size){

    void (*destroy_data)(void*) = free_data;

	HashMap *map = HashMap_create(size, destroy_data);

	recsMapPop(map, root, 0, 0x0000);

	return map;

}

int main (int argc, char *argv[]){
	//printf("%s\n", argv[1]);
	readInFile(argv[1]);
	return -1;

}





