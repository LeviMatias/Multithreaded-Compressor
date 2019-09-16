//
// Created by Matias on 13/09/2019.
//

#include "for_compressor.h"

namespace {
    int find_max(std::list<uint32_t> &nums) {
        //max is lost, lets find him
        auto it = std::max_element(std::begin(nums), std::end(nums));
        return *it;
    }

    unsigned int count_bits(uint32_t n) {
        unsigned int count = 0;
        while (n) {
            n = n >> 1;
            count++;
        }
        return count;
    }

    unsigned int find_bits_to_represent_n(std::list<uint32_t> &nums) {
        unsigned int max = find_max(nums);
        return count_bits(max);
    }

    int find_min(std::list<uint32_t> &nums) {
        auto it = std::min_element(std::begin(nums), std::end(nums));
        return *it;
    }

    int sub_smallest(std::list<uint32_t> &nums) {
        int min = find_min(nums);
        std::for_each(nums.begin(), nums.end(), [min](uint32_t &n) { n -= min; });
        return min;
    }

    int fill_int_list(std::list<uint32_t> &list, char *source, int source_size) {
        int i;
        printf("swaperino");
        for (i = 0; i < (source_size); i += BYTES_PER_NUMBER) {
            //int* ptr = (int*)(source + i);
            //int v = (int)ntohl(*ptr);
            int v = (int) *(source + i + 3);
            list.push_front(v);
        }
        return i / BYTES_PER_NUMBER;
    }

    std::vector<unsigned char> pack(std::list<uint32_t> &nums, int &bit_size) {
        //assume: max variance is of 8 bits
        const int size = ceil(bit_size * nums.size() / BITS_IN_BYTE);
        std::vector<unsigned char> bytes_v(size, 0);
        int free_bits = BITS_IN_BYTE;
        int j = 0;

        std::for_each(nums.begin(), nums.end(), [&](uint32_t &n) {
                          int bits_to_mov = bit_size;
                          auto nc = (unsigned char)n;
                          while (bits_to_mov > 0) {
                              int bits_movd = std::min(free_bits, bits_to_mov);
                              nc = (nc << (free_bits - bits_movd));
                              bytes_v[j] = bytes_v[j] | nc;

                              free_bits -= bits_movd;
                              bits_to_mov -= bits_movd;
                              if (free_bits == 0) {
                                  free_bits = BITS_IN_BYTE;
                                  j++;
                              }
                          }
                      }
        );
        return bytes_v;
    }

}

void FoRCompressor::compress(CompressResult* &r, char* to_compress,\
                            size_t source_size, size_t block_size){
    //if (to_compress->length() < (block_size * BYTES_PER_NUMBER)) {
        //fix_size(to_compress, block_size);//fill with zeroes
    //}
    std::list<uint32_t> nums;
    fill_int_list(nums, to_compress, source_size);
    int reference = sub_smallest(nums);
    int bit_size = find_bits_to_represent_n(nums);
    std::vector<unsigned char> packed_bytes = pack(nums, bit_size);
    r->set(reference, bit_size, packed_bytes);
}