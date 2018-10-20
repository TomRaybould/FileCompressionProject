
#include "bit_ops.h"

int bit_get(const unsigned char *bits, int position){
    int target_char = position / 8;
    int bit_offset  = position % 8;

    //1000 0000
    unsigned char mask = 0x80;

    mask = mask >> bit_offset;

    return ((bits[target_char] & mask) == mask) ? 1 : 0;
}


void bit_set(unsigned char *bits, int position, int state){
    int target_char = position / 8;
    int bit_offset = position % 8;

    //1000 0000
    unsigned char mask = 0x80;

    mask = mask >> bit_offset;

    if(state){
        bits[target_char] = bits[target_char] | mask;
    }
    else{
        bits[target_char] = bits[target_char] & (~mask);
    }

}