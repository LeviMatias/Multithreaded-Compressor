//
// Created by Matias on 14/09/2019.
//

#include "compress_result.h"

void compress_result::set(int reference, char bit_size, std:array<char> packed_bytes){
    this->reference = reference;
    this->bit_size = bit_size;
    this->packed_bytes = packed_bytes;
}

void compress_result::release(){
    //nothing to release
}