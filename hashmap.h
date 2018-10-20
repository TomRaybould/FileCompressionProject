
#ifndef HASHMAP_H
#define HASHMAP_H

	struct Entry_
	{
		char 	key;
		void 	*data;
		struct 	Entry_ 	*next;
	};

	typedef struct Entry_ Entry;

	Entry* 	Entry_create	(unsigned char key, void *data);
	void	Entry_destroy	(Entry *entry, void (*destroy_data)(void *));
	
	struct HashMap_
	{
		void (*destroy_data)(void *);
		Entry **entries;
		int size; 		
	};

	typedef struct HashMap_ HashMap;

	HashMap* 	HashMap_create	(int size, void (*destroy_data)(void *));
	void 		HashMap_put		(HashMap *map, unsigned char key, void *data);
	void  		HashMap_get		(HashMap *map, unsigned char key, void **data);
	void		HashMap_print	();
	void		HashMap_destroy	(HashMap *map);

#endif