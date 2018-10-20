
#ifndef HUFFMAN_H
#define HUFFMAN_H


struct HuffmanMapData_{
    unsigned int code;
    unsigned int bit_length;
};

typedef struct HuffmanMapData_ HuffmanMapData;

void HuffmanMapData_print(void* data);

#endif