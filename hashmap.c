#include <stdlib.h>
#include "hashmap.h"

int hash(int map_size, char key);

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

int hash(int map_size, char key){
	return key % map_size;
}

void HashMap_put(HashMap **map, char key, void *data){
	HashMap *m = *map;
	
	int map_size = m -> size;

	int hashed_key = hash(map_size, key);




}

Entry* HashMap_get(HashMap **map, char key);

void HashMap_print(); 

void HashMap_destroy(HashMap **map){
	HashMap *m = *map;
	free(m -> entries);
	free(m);
}