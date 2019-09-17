//
// Created by Matias on 13/09/2019.
//

#ifndef TP1_PROJECT_FOR_COMPRESSOR_H
#define TP1_PROJECT_FOR_COMPRESSOR_H

#include <list>
#include <math.h>
#include "compress_result.h"

// frame of reference compressor
class FoRCompressor {
    public:
    static void compress(CompressResult* &r, std::vector<char> &to_compress,\
                            size_t source_size, size_t block_size);
};


#endif //TP1_PROJECT_FOR_COMPRESSOR_H
