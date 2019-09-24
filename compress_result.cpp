//
// Created by Matias on 14/09/2019.
//

#include "compress_result.h"
#include <vector>


size_t get_size();

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

void CompressResult::Set(uint32_t reference, unsigned char bit_size,\
                        std::vector<unsigned char> &packed_bytes){
    this->reference = reference;
    this->bit_size = bit_size;
    this->packed_bytes = std::move(packed_bytes);
}

void CompressResult::ToVector(std::vector<char> &buffer){
    buffer.resize(sizeof(this->bit_size) + sizeof(this->reference));
    int offset = sizeof(this->reference);
    std::memcpy(buffer.data(), &this->reference, offset);
    std::memcpy(buffer.data() + offset, &this->bit_size,\
                sizeof(this->bit_size));
    buffer.insert(buffer.end(), this->packed_bytes.begin(),\
                this->packed_bytes.end());
}

size_t CompressResult::GetSize(){
    size_t s = sizeof(this->reference);
    s += sizeof(this->bit_size);
    s += this->packed_bytes.size();
    return s;
}
