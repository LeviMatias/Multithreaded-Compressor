//
// Created by Matias on 14/09/2019.
//

#include "compress_result.h"


size_t get_size();

compress_result::compress_result() {
    this->bit_size = 0;
    this->reference = 0;
    this->packed_bytes = std::vector<unsigned char>();
}

compress_result::compress_result(const compress_result &old_obj) {
    this->packed_bytes = std::vector<unsigned char>(old_obj.packed_bytes);
    this->reference = old_obj.reference;
    this->bit_size = old_obj.bit_size;
}

void compress_result::set(const uint32_t ref, const unsigned char bs,\
                        std::vector<unsigned char> &pb){
    this->reference = ref;
    this->bit_size = bs;
    this->packed_bytes = std::move(pb);
}

void compress_result::to_vector(std::vector<char> &buffer){
    buffer.resize(sizeof(this->bit_size) + sizeof(this->reference));
    int offset = sizeof(this->reference);
    std::memcpy(buffer.data(), &this->reference, offset);
    std::memcpy(buffer.data() + offset, &this->bit_size,\
                sizeof(this->bit_size));
    buffer.insert(buffer.end(), this->packed_bytes.begin(),\
                this->packed_bytes.end());
}

size_t compress_result::get_size(){
    size_t s = sizeof(this->reference);
    s += sizeof(this->bit_size);
    s += this->packed_bytes.size();
    return s;
}
