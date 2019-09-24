//
// Created by Matias on 18/09/2019.
//

#include "thread.h"

Thread::Thread(SafeStream &strm, const size_t blk_size){
    this->stream = &strm;
    this->block_size = blk_size;
}

void Thread::run(const int order, const int total_threads) {
    this->thread = std::thread(&Thread::_run, this, order, total_threads);
}

void Thread::join() {
    this->thread.join();
}

SafeStream *Thread::get_stream() {
    return this->stream;
}

size_t Thread::get_blk_sz() {
    return this->block_size;
}

