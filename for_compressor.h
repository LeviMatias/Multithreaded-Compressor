//
// Created by Matias on 13/09/2019.
//

#ifndef TP1_PROJECT_FOR_COMPRESSOR_H
#define TP1_PROJECT_FOR_COMPRESSOR_H

#include <bitset>
#include <list>
#include <math.h>
#include "compress_result.h"

#define BYTES_PER_NUMBER 4;
#define BITS_IN_BYTE 8;

// frame of reference compressor
class FoFCompressor {
    private:
    void fix_size(string* str, int block_size);

    public:

    compress_result compress(string* to_compress, int block_size);
};


#endif //TP1_PROJECT_FOR_COMPRESSOR_H
