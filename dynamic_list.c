
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_list.h"


DynamicList* DynamicList_create(int init_capacity){

	DynamicList* list = malloc(sizeof(DynamicList));
	
	list -> size 			= 0;
	void *p_data			= malloc(sizeof(void *) * init_capacity);
	list -> data			= (void(*)) p_data;
	list -> _capacity 		= init_capacity;

	return list;

}

void DynamicList_add(DynamicList **list, void *element){
	
	DynamicList *l = *list;

	if(l -> size >= l -> _capacity){

		int new_capacity = l -> _capacity * 2;

		void *new_arr = realloc((l -> data), new_capacity);

		free(*(l -> data));

		*(l -> data) = new_arr;

	}

	(l -> data)[l -> size] = element;
	l -> size++;

}

void DynamicList_trim(DynamicList **list){

	DynamicList *l = *list;

	int curr_size = l -> size;

	void *new_arr = realloc((l -> data), curr_size);

	free(*(l -> data));

	*(l -> data) = new_arr;

	return;	
} 

void DynamicList_print(DynamicList **list, char* (*print_func) (void *element)){
	DynamicList *l = *list;
	void **data = l -> data;

	for (int i = 0; i < l -> size; i++){
		printf("%s\n", print_func(data[i]));
	}

}



