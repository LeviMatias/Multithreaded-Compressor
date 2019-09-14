//
// Created by Matias on 14/09/2019.
//

#ifndef TP1_PROJECT_COMPRESS_RESULT_H
#define TP1_PROJECT_COMPRESS_RESULT_H

#include <array>

class compress_result {
    public:
    int reference;
    char bit_size;
    std:array<char> packed_bytes;

    public:
    void set(int reference, char bit_size, std:array<char> packed_bytes);
    void release();
};


#endif //TP1_PROJECT_COMPRESS_RESULT_H
