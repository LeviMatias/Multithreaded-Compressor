//
// Created by Matias on 18/09/2019.
//

#include "thread.h"

Thread::Thread(safe_stream &strm, size_t blk_size){
    this->stream = &strm;
    this->block_size = blk_size;

}

void Thread::run(turn_scheduler &ts) {
    this->thread = std::thread(&Thread::_run, this, std::ref(ts));
}

void Thread::join() {
    this->thread.join();
}

safe_stream *Thread::get_stream() {
    return this->stream;
}

size_t Thread::get_blk_sz() {
    return this->block_size;
}

