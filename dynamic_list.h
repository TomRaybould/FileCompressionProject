
#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

struct DynamicList_
{
	void 	(*destroy_element)(void* data);
	int     size;
	void    ** data;
	int 	_capacity;
};


typedef struct DynamicList_ DynamicList;

int DynamicList_init(DynamicList *list, int init_capacity, void (*destroyElement)(void *data));
int	DynamicList_add		(DynamicList *list, void *element);
int DynamicList_trim	(DynamicList *list);
int DynamicList_destroy	(DynamicList *list);
void DynamicList_print	(DynamicList *list, char* (*print_func) (void *element));


#endif
