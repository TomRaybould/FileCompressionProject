#ifndef OCCURRENCE_H
#define OCCURRENCE_H

struct HuffmanNode_
{
	int weight;
	char value;
};

typedef struct HuffmanNode_ HuffmanNode;


HuffmanNode* 	HuffmanNode_create		(char value, int weight);
void 			HuffmanNode_destroy		(HuffmanNode *node);

struct HuffmanNodeHeap_
{
	int capacity;
	int size;
	HuffmanNode *data;
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