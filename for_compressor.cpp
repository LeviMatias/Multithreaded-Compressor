//
// Created by Matias on 13/09/2019.
//

#include "for_compressor.h"

int find_max(int* nums, int block_size){
    //max is lost, lets find him
    auto it = std::max_element(nums->front(), nums->end());
    return it*;
}

int count_bits(unsigned int n){
    unsigned int count = 0;
    while (n >>= 1){
        count++;
    }
    return count;
}

int find_bits_to_represent_n(std::list<int> &nums){
    unsigned int max = find_max(nums);
    return count_bits(max);
}

int find_min(std::list<int> &nums){
    auto it = std::min_element(nums.front(), nums.end());
    return it*;
}

int sub_smallest(std::list<int> &nums){
    int min = find_min(nums);
    std::for_each(nums.begin(), nums.end(), [](int &n){ n -= min; });
    return min;
}

void fill_int_list(std::list<int> &list, string* source){
    for (int i=0; i<(source->length() - 1)); i+= BYTES_PER_NUMBER){
        int v = source[i];
        list.push_front(v);
    }
}

char make_mask(int n){
    char mask = 0;
    for (int i=0; i<n; i++){
        mask++;// turns first bit
        mask<<1;//pushes it
    }
    mask++;//turns first bit
    return mask;
}

int move_bits(char &dest, char &source,int bits){

}

std:array<char> pack(std::list<int> &nums, int bit_size){
    //assume: max variance is of 8 bits
    const int size = ceil((bitsize*nums.size())/BITS_IN_BYTE);
    std:array<char, size> bytes = {0};
    int free_bits = BITS_IN_BYTE;
    int j = 0;

    std::for_each(nums.begin(), nums.end(), [](int &n){
        int bits_to_move = bit_size;
        while(bits_to_move > 0){
            int bits_moved = min(free_bits, bits_to_move);
            bytes[j] | ((*n & mask) << (free_bits - bits_moved));

            free_bits -= bits_moved;
            bits_to_move -= bits_moved;
            if (free_bits == 0){
                free_bits = BITS_IN_BYTE;
                j++;
            }
        }
    }
    );
    return bytes;
}


compress_result FoFCompressor::compress(string* to_compress, int block_size){
    if (to_compress->length() < (block_size * BYTES_PER_NUMBER)) {
        fix_size(to_compress, block_size);//fill with zeroes
    }
    std::list<int> nums;
    fill_int_list(nums, to_compress);
    int reference = sub_smallest(nums);
    int bit_size = find_bits_to_represent_n(nums);
    std:array<char> packed_bytes = pack(nums, bit_size);
    compress_result result;
    result.set(reference, bit_size, packed_bytes);
}
