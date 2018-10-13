#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

struct HuffmanTreeNode_
{
	unsigned char value;
	double weight;
	struct HuffmanTreeNode_ *left;
	struct HuffmanTreeNode_ *right;
};

typedef struct HuffmanTreeNode_ HuffmanTreeNode;

HuffmanTreeNode*	HuffmanTreeNode_create		(char value, double weight, HuffmanTreeNode *left, HuffmanTreeNode *right);
void 				HuffmanTreeNode_destroy		(HuffmanTreeNode *node);

struct HuffmanNodeHeap_
{
	int capacity;
	int size;
	HuffmanTreeNode **data;
};

typedef struct HuffmanNodeHeap_ HuffmanNodeHeap;

HuffmanNodeHeap* 	HuffmanNodeHeap_create	(int size);
void 				HuffmanNodeHeap_push	(HuffmanNodeHeap **heap, HuffmanTreeNode *node);
HuffmanTreeNode* 	HuffmanNodeHeap_pop		(HuffmanNodeHeap **heap);
void 				HuffmanNodeHeap_print	(HuffmanNodeHeap *heap);

struct Occurrence_
{
	char value;
	int  numOfOccurrences; 
};


typedef struct Occurrence_ Occurrence;

void destroyOccurrence(void *data);

#endif