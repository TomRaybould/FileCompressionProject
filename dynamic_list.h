
#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

struct DynamicList_
{
	int size;
	void ** data;
	int _capacity;
};


typedef struct DynamicList_ DynamicList;

DynamicList* 	DynamicList_create	(int init_capacity);
void 			DynamicList_add		(DynamicList **list, void *element); 
void 			DynamicList_trim	(DynamicList **list); 
void 			DynamicList_print	(DynamicList **list, char* (*print_func) (void *element));


#endif