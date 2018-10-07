#include <stdlib.h>
#include "hashmap.h"

int hash(int map_size, unsigned char key);


Entry* Entry_create(unsigned char key, void* data, int data_bit_length){
	Entry *newEntry = malloc(sizeof(Entry));

	newEntry 	-> key 			= key;
	newEntry	-> data 		= data;
	newEntry 	-> bit_length 	= data_bit_length;
	newEntry	-> next 		= NULL;

	return newEntry;
}


void Entry_destroy(Entry **entry){
	free(*entry);
}



HashMap* HashMap_create(int size){

	Entry **entries 	= malloc(sizeof(Entry*) * size);
	HashMap *hashmap 	= malloc(sizeof(HashMap));

	for(int i = 0; i < size; i ++){
		entries[i] = NULL;
	}

	hashmap -> size 	= size;
	hashmap -> entries 	= entries;

	return hashmap;

}

int hash(int map_size, unsigned char key){
	return key % map_size;
}

void HashMap_put(HashMap **map, unsigned char key, void *data, int data_bit_length){

	HashMap *m = *map;
	int map_size = m -> size;
	int hashed_key = hash(map_size, key);

	Entry *newEntry = Entry_create(key, data, data_bit_length);
	Entry **entries = m -> entries;  

	//if null add new entry
	if(entries[hashed_key] == NULL){
		entries[hashed_key] = newEntry;
		return;
	}

	//go to the end of the entry listed list add to last element
	Entry *curr = entries[hashed_key];
	
	while(curr -> next != NULL){
		curr = curr -> next;
	}

	curr -> next = newEntry;

}

Entry* HashMap_get(HashMap **map, unsigned char key){

	HashMap *m = *map;
	int map_size = m -> size;
	int hashed_key = hash(map_size, key);

	Entry **entries = m -> entries;  

	//search the linkedlist for value
	Entry *curr = entries[hashed_key];
	
	while(curr != NULL){
		//found a match for key
		if(curr -> key == key){
			return curr;
		}

		curr = curr -> next;
	}

	//no match found
	return NULL;
}

void HashMap_print(); 

void HashMap_destroy(HashMap **map){
	HashMap *m = *map;
	free(m -> entries);
	free(m);
}