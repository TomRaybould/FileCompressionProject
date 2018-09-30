#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

struct HuffmanNode_
{
	int weight;
	char value;
	struct HuffmanNode_ *left;
	struct HuffmanNode_ *right;
};

typedef struct HuffmanNode_ HuffmanNode;


HuffmanNode* 	HuffmanNode_create		(char value, int weight, HuffmanNode *left, HuffmanNode *right);
void 			HuffmanNode_destroy		(HuffmanNode *node);

struct HuffmanNodeHeap_
{
	int capacity;
	int size;
	HuffmanNode **data;
};

typedef struct HuffmanNodeHeap_ HuffmanNodeHeap;

HuffmanNodeHeap* 	HuffmanNodeHeap_create	(int size);
void 				HuffmanNodeHeap_push	(HuffmanNodeHeap **heap, HuffmanNode node);
HuffmanNode* 		HuffmanNodeHeap_pop		(HuffmanNodeHeap **heap);
void 				HuffmanNodeHeap_print	(HuffmanNodeHeap *heap);

struct Occurrence_
{
	char value;
	int  numOfOccurrences; 
};


typedef struct Occurrence_ Occurrence;

#endif