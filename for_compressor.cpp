//
// Created by Matias on 13/09/2019.
//

#include "for_compressor.h"
#include <algorithm>
#include <vector>
#include <list>

namespace {
    unsigned int count_bits(uint32_t n){
        unsigned int count = 0;
        while (n) {
            n = n >> 1;
            count++;
        }
        return count;
    }

    unsigned int find_bits_to_represent_n(std::list<uint32_t> &ns) {
        unsigned int max = *std::max_element(std::begin(ns), std::end(ns));
        return count_bits(max);
    }

    uint32_t sub_smallest(std::list<uint32_t> &nums) {
        uint32_t min = *std::min_element(std::begin(nums), std::end(nums));
        std::for_each(nums.begin(), nums.end(), [min](uint32_t &n){
            n -= min;
        });
        return min;
    }

    void fill_int_list(std::list<uint32_t> &list, std::vector<char> &source,\
    size_t block_size){
        unsigned int i,j;
        uint32_t v = 0;
        for (i = 0; i < source.size(); i += BYTES_PER_NUMBER) {
            int* ptr = (int*)&source[i];
            v = ntohl(*ptr);
            list.push_back(v);
        }
        for (j=block_size - list.size(); j>0; j--){
            list.push_back(v);//fill list to match blocksize
        }
    }

    std::vector<unsigned char> pack(std::list<uint32_t> &nums,\
                                    const size_t bit_s){
        float f = (float)(bit_s * nums.size()) / (float)BITS_IN_BYTE;
        const int size = ceil(f);
        std::vector<unsigned char> bytes_v(size, 0);
        unsigned int free_bits = BITS_IN_BYTE;
        int j = 0;

        std::for_each(nums.begin(), nums.end(), [&](uint32_t &n){
            unsigned int bits_to_mov = bit_s;
            uint32_t nc = n;
            while (bits_to_mov > 0) {
                 unsigned int over_bits = std::max(\
                                    (int)(bits_to_mov - free_bits), 0);
                unsigned int bits_mov = std::min(free_bits, bits_to_mov);
                unsigned int n = nc >> (over_bits);
                int dif = free_bits - bits_mov;
                n = n<<(dif);
                bytes_v[j] = bytes_v[j] | (n);

                free_bits -= bits_mov;
                bits_to_mov -= bits_mov;
                if (free_bits == 0) {
                  free_bits = BITS_IN_BYTE;
                  j++;
                }
            }
        });
        return bytes_v;
    }

}

compress_result FoRCompressor::compress(std::vector<char>\
                        &to_compress,size_t block_size){
    std::list<uint32_t> nums;
    fill_int_list(nums, to_compress, block_size);
    uint32_t reference = sub_smallest(nums);
    size_t bit_size = find_bits_to_represent_n(nums);
    std::vector<unsigned char> packed_bytes = pack(nums, bit_size);
    compress_result r;
    r.set(htonl(reference), bit_size, packed_bytes);
    return r;
}
