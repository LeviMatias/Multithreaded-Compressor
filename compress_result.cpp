//
// Created by Matias on 14/09/2019.
//

#include "compress_result.h"


size_t get_size();

CompressResult::CompressResult() {
    this->bit_size = 0;
    this->reference = 0;
    this->packed_bytes = std::vector<unsigned char>();
    this->finished = true;
    this->ready = true;
}

CompressResult::CompressResult(const CompressResult &old_obj) {
    this->packed_bytes = std::vector<unsigned char>(old_obj.packed_bytes);
    this->reference = old_obj.reference;
    this->bit_size = old_obj.bit_size;
}

void CompressResult::set(uint32_t ref, unsigned char bs, std::vector<unsigned char> &pb){
    this->reference = ref;
    this->bit_size = bs;
    this->packed_bytes = std::move(pb);
    this->ready = true;
}

void CompressResult::print_to_cout() {
    std::cout<< "num: " << this->reference << +this->bit_size;
    std::for_each(this->packed_bytes.begin(), this->packed_bytes.end(), [&](unsigned char &n){
        for (int i= BITS_IN_BYTE-1; i >= 0; i--){
            unsigned int mask =  1 << i;
            unsigned int masked_n = n & mask;
            unsigned int bit = masked_n >> i;
            std::printf("%d",bit);
        }
    });
    std::cout<<std::endl;
}

void CompressResult::to_vector(std::vector<char> &buffer){
    buffer.resize(sizeof(this->bit_size) + sizeof(this->reference));
    int offset = sizeof(this->reference);
    std::memcpy(buffer.data(), &this->reference, offset);
    std::memcpy(buffer.data() + offset, &this->bit_size, sizeof(this->bit_size));
    buffer.insert(buffer.end(), this->packed_bytes.begin(), this->packed_bytes.end());
}

size_t CompressResult::get_size(){
    size_t s = sizeof(this->reference);
    s += sizeof(this->bit_size);
    s += this->packed_bytes.size();
    return s;
}

bool CompressResult::is_ready() {
    return this->ready;
}

bool CompressResult::is_finished() {
    return this->finished;
}

void CompressResult::reset() {
    this->ready = false;
}

void CompressResult::finish() {
    this->finished = true;
}
