//
// Created by Matias on 13/09/2019.
//

#include "for_compressor.h"

static bool abs_compare(int a, int b)
{
    return (std::abs(a) < std::abs(b));
}

int find_max(std::list<int> &nums){
    //max is lost, lets find him
    auto it = std::max_element(std::begin(nums), std::end(nums));
    return *it;
}

int count_bits(unsigned int n){
    unsigned int count = 0;
    while (n){
        n = n >> 1;
        count++;
    }
    return count;
}

int find_bits_to_represent_n(std::list<int> &nums){
    unsigned int max = find_max(nums);
    return count_bits(max);
}

int find_min(std::list<int> &nums){
    auto it = std::min_element(std::begin(nums), std::end(nums));
    return *it;
}

int sub_smallest(std::list<int> &nums){
    int min = find_min(nums);
    std::for_each(nums.begin(), nums.end(), [min](int &n){ n -= min; });
    return min;
}

int fill_int_list(std::list<int> &list, char* source,  int source_size){
    int i;
    printf("swaperino");
    for (i=0;  i < (source_size) ; i+= BYTES_PER_NUMBER){
        //int* ptr = (int*)(source + i);
        //int v = (int)ntohl(*ptr);
        int v = (int)*(source + i + 3);
        list.push_front(v);
    }
    return i/BYTES_PER_NUMBER;
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

std::vector<char> pack(std::list<int> &nums, int &bit_size){
    //assume: max variance is of 8 bits
    const int size = ceil(bit_size*nums.size()/BITS_IN_BYTE);
    std::vector<char> bytes_v (size, 0);
    int free_bits = BITS_IN_BYTE;
    int j = 0;

    std::for_each(nums.begin(), nums.end(),[&](int &n){
        int bits_to_move = bit_size;
        char nc = (char)n;
        while(bits_to_move > 0){
            int bits_moved = std::min(free_bits, bits_to_move);
            nc = (nc << (free_bits - bits_moved));
            bytes_v[j] = bytes_v[j] | nc;

            free_bits -= bits_moved;
            bits_to_move -= bits_moved;
            if (free_bits == 0){
                free_bits = BITS_IN_BYTE;
                j++;
            }
        }
    }
    );
    return bytes_v;
}


CompressResult FoFCompressor::compress(char* to_compress, int source_size, int block_size){
    //if (to_compress->length() < (block_size * BYTES_PER_NUMBER)) {
        //fix_size(to_compress, block_size);//fill with zeroes
    //}
    std::list<int> nums;
    fill_int_list(nums, to_compress, source_size);
    int reference = sub_smallest(nums);
    int bit_size = find_bits_to_represent_n(nums);
    std::vector<char> packed_bytes = pack(nums, bit_size);
    CompressResult result;
    result.set(reference, bit_size, packed_bytes);
    return result;
}