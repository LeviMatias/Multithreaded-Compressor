//
// Created by Matias on 15/09/2019.
//

#include "compressor_thread.h"
#include <vector>

CompressorThread::CompressorThread(SafeStream &stream, size_t block_size,\
                    CoordinatedQueue<CompressResult> &rq)\
                    : Thread(stream, block_size){
    this->q = &rq;
}

void CompressorThread::_Run(const int order, const int total_threads) {
    int r = 1;
    unsigned int i = 0;
    const size_t size = this->GetBlockSize() * BYTES_PER_NUMBER;
    while (r > 0){
        std::vector<char> blk(size,0);
        unsigned int index = (total_threads*i + order)*size;
        r = this->GetStream()->Read(blk.data(), index, size);
        if (r != 0){
            blk.resize(std::abs(r));
            (*this->q).AddElement(FoRCompressor::Compress\
                            (blk, this->GetBlockSize()));
        }
        i++;
    }
    (*this->q).CloseQueue();
}
