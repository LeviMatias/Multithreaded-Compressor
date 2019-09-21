//
// Created by Matias on 13/09/2019.
//

#ifndef TP1_PROJECT_FOR_COMPRESSOR_H
#define TP1_PROJECT_FOR_COMPRESSOR_H

#include <list>
#include <math.h>
#include "compress_result.h"
#include <winsock2.h>

// frame of reference compressor
class FoRCompressor {
    public:
    //PRE: to_compress contains the 4-byte numbers to be compress
    //
    //POS compresses to_compress into compress_result r
    static void compress(CompressResult &r, std::vector<char> &to_compress,\
                         size_t block_size);
};


#endif //TP1_PROJECT_FOR_COMPRESSOR_H
