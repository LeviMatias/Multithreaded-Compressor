//
// Created by Matias on 15/09/2019.
//

#include "compressor_thread.h"
#include <vector>

compressor_thread::compressor_thread(safe_stream &stream, size_t block_size,\
                    coordinated_queue<compress_result> &rq)\
                    : Thread(stream, block_size){
    this->q = &rq;
}

void compressor_thread::_run(const int order, const int total_threads) {
    unsigned int r = 1;
    unsigned int i = 0;
    const size_t size = this->get_blk_sz() * BYTES_PER_NUMBER;
    while (r != 0){
        std::vector<char> blk(size,0);
        unsigned int index = (total_threads*i + order - 1)*size;
        r = this->get_stream()->read(&blk[0], index, size);
        if (r != 0){
            blk.resize(r);
            (*this->q).add_element(FoRCompressor::compress\
                                (blk, this->get_blk_sz()));
        }
        i++;
    }
    (*this->q).close_queue();
}
