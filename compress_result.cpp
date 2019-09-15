//
// Created by Matias on 14/09/2019.
//

#include "compress_result.h"

void CompressResult::set(int reference, char bit_size, std::vector<char> packed_bytes){
    this->reference = reference;
    this->bit_size = bit_size;
    this->packed_bytes = packed_bytes;
}

void CompressResult::print_to_cout() {
    std::string str(this->packed_bytes.begin(), this->packed_bytes.end());
    std::cout<< "num: " << this->reference << this->bit_size << str << std::endl;
}

void CompressResult::release(){
    //nothing to release
}