#include <stdlib.h>
#include "hashmap.h"

int hash(char key);

HashMap* HashMap_create(int size){

	Entry *entries 		= malloc(sizeof(Entry) * size);
	HashMap *hashmap 	= malloc(sizeof(HashMap));

	hashmap -> size 	= size;
	hashmap -> entries 	= entries;

	return hashmap;
	
}

void 		HashMap_put(HashMap **map, char key, void *data);

Entry* 		HashMap_get(HashMap **map, char key);

void		HashMap_print(); 

void HashMap_destroy(HashMap **map){
	HashMap *m = *map;
	free(m -> entries);
	free(m);
}