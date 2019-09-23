//
// Created by Matias on 18/09/2019.
//

#ifndef TP1_PROJECT_THREAD_H
#define TP1_PROJECT_THREAD_H


#include <thread>
#include "safe_stream.h"

class Thread {
private:
    std::thread thread;
    safe_stream* stream;
    size_t block_size;

    virtual void _run(int order, int total_threads) = 0;

protected:
    safe_stream*  get_stream();
    size_t get_blk_sz();

public:
    explicit Thread(safe_stream &stream, size_t block_size);

    //runs the thread with the specified id
    void run(int order, int total_threads);

    //joins the thread
    void join();
};


#endif //TP1_PROJECT_THREAD_H
