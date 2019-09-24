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
    const size_t size = this->GetBlockSize() * BYTES_PER_NUMBER;
    unsigned int r = size;
    unsigned int i = 0;
    while (r == size){
        std::vector<char> blk(size,0);
        unsigned int index = (total_threads*i + order)*size;
        r = this->GetStream()->Read(blk.data(), index, size);
        if (r != 0){
            blk.resize(r);
            (*this->q).AddElement(FoRCompressor::Compress\
                            (blk, this->GetBlockSize()));
        }
        i++;
    }
    (*this->q).CloseQueue();
}
