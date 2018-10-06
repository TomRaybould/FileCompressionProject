
#ifndef HASHMAP_H
#define HASHMAP_H

	struct Entry_
	{
		int 	key;
		void 	*data;
		int		bit_length;
		struct 	Entry_ 	*next;
	};

	typedef struct Entry_ Entry;

	struct HashMap_
	{
		Entry *entries;
		int size; 		
	};

	typedef struct HashMap_ HashMap;

	HashMap* 	HashMap_create(int size);
	void 		HashMap_put(HashMap **map, char key, void *data);
	Entry* 		HashMap_get(HashMap **map, char key);
	void		HashMap_print();
	void		HashMap_destroy(HashMap **map);

#endif