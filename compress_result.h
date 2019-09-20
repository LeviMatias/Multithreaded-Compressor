//
// Created by Matias on 14/09/2019.
//

#ifndef TP1_PROJECT_COMPRESS_RESULT_H
#define TP1_PROJECT_COMPRESS_RESULT_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>

#define BYTES_PER_NUMBER 4
#define BITS_IN_BYTE 8

class CompressResult {
    private:
    uint32_t reference;
    unsigned char bit_size;
    //problem: bitset needs compile time size
    //bitset and vector<bool> are not containers so
    //the passing needs to be done bit to bit
    //neither guarantee elements are next to each other
    //solution vector char can receive multiple bits through masking
    //con: harder to print to cout
    std::vector<unsigned char> packed_bytes;

    public:
    CompressResult();
    CompressResult(const CompressResult &old_obj);
    void set(uint32_t reference, unsigned char bit_size,\
            std::vector<unsigned char> &packed_bytes);

    void print_to_cout();
    void to_vector(std::vector<char> &buffer);
    void release();

    size_t get_size();
};


#endif //TP1_PROJECT_COMPRESS_RESULT_H
