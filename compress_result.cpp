//
// Created by Matias on 14/09/2019.
//

#include "compress_result.h"

#include <utility>

CompressResult::CompressResult() {
    this->bit_size = 0;
    this->reference = 0;
    this->packed_bytes = std::vector<unsigned char>();
}

CompressResult::CompressResult(const CompressResult &old_obj) {
    this->packed_bytes = std::vector<unsigned char>(old_obj.packed_bytes);
    this->reference = old_obj.reference;
    this->bit_size = old_obj.bit_size;
}

void CompressResult::set(int ref, char bs, std::vector<unsigned char> &pb){
    this->reference = ref;
    this->bit_size = bs;
    this->packed_bytes = std::move(pb);
}

void CompressResult::print_to_cout() {
    std::string str(this->packed_bytes.begin(), this->packed_bytes.end());
    std::cout<< "num: " << this->reference << this->bit_size << str << std::endl;
}

void CompressResult::release(){
    //nothing to release
}
