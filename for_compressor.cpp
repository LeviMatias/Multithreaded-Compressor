//
// Created by Matias on 13/09/2019.
//

#include "for_compressor.h"


void compress(string* to_compress, int block_size){
    if (to_compress->length() < (block_size * BYTES_PER_NUMBER)) {
        fix_size(to_compress, block_size);//fill with zeroes
    }
    //find smallest
    //sub smallest
    //find biggest
    //get bits
    //make
}
