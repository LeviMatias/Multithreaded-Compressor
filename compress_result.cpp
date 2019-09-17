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
    std::cout<< "num: " << this->reference << +this->bit_size;
    std::for_each(this->packed_bytes.begin(), this->packed_bytes.end(), [&](unsigned char &n){
        for (int i= BITS_IN_BYTE-1; i >= 0; i--){
            int mask =  1 << i;
            int masked_n = n & mask;
            int bit = masked_n >> i;
            std::printf("%d",bit);
        }
    });
    std::cout<<std::endl;
}

void CompressResult::write(){

}

void CompressResult::release(){
    //nothing to release
}
