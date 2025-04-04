#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

int hash(int map_size, unsigned char key);


Entry* Entry_create(unsigned char key, void *data){
	Entry *newEntry = malloc(sizeof(Entry));

	newEntry 	-> key 			= key;
	newEntry	-> data 		= data;
	newEntry	-> next 		= NULL;

	return newEntry;
}

HashMap* HashMap_create(int size, void (*destroy_data)(void *), void (*print_data)(void *)){

	Entry **entries 	= malloc(sizeof(Entry*) * size);
	HashMap *map		= malloc(sizeof(HashMap));

	for(int i = 0; i < size; i++){
		entries[i] = NULL;
	}

	map -> print_data	= print_data;
	map -> destroy_data = destroy_data;
	map -> size 		= size;
	map -> entries 		= entries;

	return map;

}

int hash(int map_size, unsigned char key){
	return key % map_size;
}

void HashMap_put(HashMap *map, unsigned char key, void *data){

	int map_size = map -> size;
	int hashed_key = hash(map_size, key);

	Entry *newEntry = Entry_create(key, data);
	Entry **entries = map -> entries;

	//if null add new entry
	if(entries[hashed_key] == NULL){
		entries[hashed_key] = newEntry;
		return;
	}

	//go to the end of the entry listed list add to last element
	Entry *curr = entries[hashed_key];
	
	while (curr -> next != NULL){
		curr = curr -> next;
	}

	curr -> next = newEntry;
}

void HashMap_get(HashMap *map, unsigned char key, void **data){

	//printf("Key : %c \n", key);
	int map_size = map -> size;
	int hashed_key = hash(map_size, key);

	Entry **entries = map -> entries;

	//search the linked list for value
	Entry *curr = entries[hashed_key];

	*data = NULL;

	while(curr != NULL){
		//found a match for key
		if(curr -> key == key){
			//printf("%c \n", curr -> key);
			*data = curr -> data;
			break;
		}
		curr = curr -> next;
	}

}

void HashMap_print(HashMap *map){
	printf("Printing HashMap... \n");

	if(map -> print_data == NULL){
		printf("No print function provided\n\n");
		return;
	}

	int size = map -> size;
	Entry **entries = map -> entries;

	for(int i = 0; i < size; i++){
		Entry *entry = entries[i];
		if(entry == NULL){
			continue;
		}

		while(entry != NULL){
			printf("%u: ", entry -> key);
			map -> print_data(entry -> data);

			if(entry -> next != NULL){
				printf("-> ");
			}
			entry = entry -> next;
		}
		printf("\n");
	}

}

void HashMap_destroy(HashMap *map){

	Entry **entries = map -> entries;
	int size = map -> size;

	for(int i = 0; i < size; i++){
		Entry_destroy(entries[i], map -> destroy_data);
	}

	free(map -> entries);
	free(map);
}

void Entry_destroy(Entry *entry, void (*destroy_data)(void *)){
	if(entry == NULL){
		return;
	}

	Entry_destroy(entry -> next, destroy_data);

	if(destroy_data != NULL) {
		destroy_data(entry->data);
	}
}
