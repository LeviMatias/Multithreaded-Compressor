//
// Created by Matias on 18/09/2019.
//

#include "thread.h"

Thread::Thread(SafeStream &strm, const size_t blk_size){
    this->stream = &strm;
    this->block_size = blk_size;
}

void Thread::Run(const int order, const int total_threads) {
    this->thread = std::thread(&Thread::_Run, this, order, total_threads);
}

void Thread::Join() {
    this->thread.join();
}

SafeStream *Thread::GetStream() {
    return this->stream;
}

size_t Thread::GetBlockSize() {
    return this->block_size;
}

