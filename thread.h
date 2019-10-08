//
// Created by Matias on 18/09/2019.
//

#ifndef TP1_PROJECT_THREAD_H
#define TP1_PROJECT_THREAD_H


#include <thread>
#include <pthread.h>
#include "safe_stream.h"

class Thread {
private:
    std::thread thread;
    SafeStream* stream;
    size_t block_size;

    virtual void _Run(int order, int total_threads) = 0;

protected:
    SafeStream*  GetStream();
    size_t GetBlockSize();

public:
    explicit Thread(SafeStream &stream, size_t block_size);

    //runs the thread with the specified id
    void Run(int order, int total_threads);

    //joins the thread
    void Join();
};


#endif //TP1_PROJECT_THREAD_H
