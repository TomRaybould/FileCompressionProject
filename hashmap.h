
#ifndef HASHMAP_H
#define HASHMAP_H

	struct Entry_
	{
		char 	key;
		void 	*data;
		int		bit_length;
		struct 	Entry_ 	*next;
	};

	typedef struct Entry_ Entry;

	Entry* 	Entry_create	(unsigned char key, void* data, int data_bit_length);
	void	Entry_destroy	(Entry **entry);
	
	struct HashMap_
	{
		Entry **entries;
		int size; 		
	};

	typedef struct HashMap_ HashMap;

	HashMap* 	HashMap_create	(int size);
	void 		HashMap_put		(HashMap **map, unsigned char key, void *data, int data_bit_length);
	Entry* 		HashMap_get		(HashMap **map, unsigned char key);
	void		HashMap_print	();
	void		HashMap_destroy	(HashMap **map);

#endif