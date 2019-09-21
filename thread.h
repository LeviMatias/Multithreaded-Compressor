//
// Created by Matias on 18/09/2019.
//

#ifndef TP1_PROJECT_THREAD_H
#define TP1_PROJECT_THREAD_H


#include <thread>
#include "result_queue.h"
#include "safe_stream.h"
#include "turn_scheduler.h"

class Thread {
private:
    std::thread thread;
    bool turn;
    int id;
    safe_stream strm;
    int block_size;

    virtual void _run(turn_scheduler &ts) = 0;

public:

    explicit Thread(safe_stream &stream, size_t block_size);

    void run(turn_scheduler &ts);

    void join();
};


#endif //TP1_PROJECT_THREAD_H
