
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_list.h"


int DynamicList_init(DynamicList *list, int init_capacity, void (*destroy_element)(void *)){

	void *data = malloc((sizeof(void *)) * init_capacity);

	if(data == NULL){
		return -1;
	}

	list -> size 			= 0;
	list -> data 			= data;
	list -> _capacity 		= init_capacity;
	list -> destroy_element 	= destroy_element;

	return 0;

}

int DynamicList_add(DynamicList *list, void *element){

	int list_size = list -> size;

	if(list_size >= list -> _capacity){

		int new_capacity = (list -> _capacity) * 2;

		void **data = realloc(list -> data, ((sizeof(void*)) * new_capacity));

		if(data == NULL){
			return -1;
		}

		list -> data = data;

		list -> _capacity = new_capacity;
	}

	(list->data)[list_size] = element;
	list -> size = list_size + 1;
	return 0;
}

int DynamicList_trim(DynamicList *list){

	int curr_size = list -> size;

	void **data = realloc(list -> data, ((sizeof(void*)) * curr_size));

	if(data == NULL){
		return -1;
	}

	list -> data = data;

	list -> _capacity = curr_size;

	return 0;
}


int DynamicList_destroy	(DynamicList *list){

	int list_size = list -> size;
	void **data	= list -> data;
	void (*destroy_element)(void* element) = list -> destroy_element;

	for(int i = 0; i < list_size; i++){
		void *element = data[i];

		if(element == NULL){
			continue;
		}

		destroy_element(element);

	}

	free(data);
	free(list);

	return 0;
}






