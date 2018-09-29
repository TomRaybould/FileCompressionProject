#ifndef OCCURRENCE_H
#define OCCURRENCE_H

struct HuffmanNode_
{
	int weight;
	char value;
	struct HuffmanNode_ *left;
	struct HuffmanNode_ *right;
};

typedef struct HuffmanNode_ HuffmanNode;

struct HuffmanNodeHeap_
{
	int capacity;
	int *size;
	HuffmanNode *data;
};

typedef struct HuffmanNodeHeap_ HuffmanNodeHeap;

HuffmanNodeHeap* 	HuffmanNodeHeap_create	(int size);
void 				HuffmanNodeHeap_push	(HuffmanNodeHeap *heap, HuffmanNode node);
HuffmanNode 		HuffmanNodeHeap_pop		();
void 				HuffmanNodeHeap_print	(HuffmanNodeHeap *heap);

struct Occurrence_
{
	char value;
	int  numOfOccurrences; 
};


typedef struct Occurrence_ Occurrence;

#endif