//
// Created by Matias on 14/09/2019.
//

#ifndef TP1_PROJECT_COMPRESS_RESULT_H
#define TP1_PROJECT_COMPRESS_RESULT_H

#include <vector>
#include <string>
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
    std::vector<unsigned char> packed_bytes;

    public:
    CompressResult();

    CompressResult(const CompressResult &old_obj);

    //POS sets the specified values to the result, packed_bytes is moved
    void Set(uint32_t reference, unsigned char bit_size,\
            std::vector<unsigned char> &packed_bytes);

    //PRE values must have been set previously
    //POS writes result to buffer (buffer may be resized)
    void ToVector(std::vector<char> &buffer);

    //POS returns size in bytes of the result
    size_t GetSize();
};


#endif //TP1_PROJECT_COMPRESS_RESULT_H
