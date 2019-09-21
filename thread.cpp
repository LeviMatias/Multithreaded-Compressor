//
// Created by Matias on 18/09/2019.
//

#include "thread.h"

Thread::Thread(safe_stream &stream, size_t block_size){
    this->turn = false;
}

void Thread::run(turn_scheduler &ts) {
    this->turn = false;
    this->thread = std::thread(&Thread::_run, this, std::ref(ts);
}

void Thread::join() {
    this->thread.join();
}

