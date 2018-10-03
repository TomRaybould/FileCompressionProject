
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_list.h"


DynamicList* DynamicList_create(int init_capacity){

	DynamicList* list = malloc(sizeof(DynamicList));
	
	list -> size 			= 0;
	list -> data 			= malloc((sizeof(void *)) * init_capacity);
	list -> _capacity 		= init_capacity;
	return list;

}

void DynamicList_add(DynamicList **list, void *element){
	DynamicList *l = *list;

	if(l -> size >= l -> _capacity){

		int new_capacity = (l -> _capacity) * 2;

		l -> data = realloc(l -> data, ((sizeof(void*)) * new_capacity));

		l -> _capacity = new_capacity;
	}

	(l->data)[l -> size] = element;
	l -> size = (l -> size) + 1;
}

void DynamicList_trim(DynamicList **list){

	DynamicList *l = *list;

	int curr_size = l -> size;

	l -> data = realloc(l -> data, ((sizeof(void*)) * curr_size));

	l -> _capacity = curr_size;

	return;	
} 

void DynamicList_print(DynamicList **list, char* (*print_func) (void *element)){
	DynamicList *l = *list;
	void **data = l -> data;

	for (int i = 0; i < l -> size; i++){
		printf("%s\n", print_func(data[i]));
	}

}



