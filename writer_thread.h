//
// Created by Matias on 16/09/2019.
//

#ifndef TP1_PROJECT_WRITER_THREAD_H
#define TP1_PROJECT_WRITER_THREAD_H

#include "safe_stream.h"
#include "result_queue.h"
#include "thread.h"

class writer_thread : public Thread {
private:
    safe_queue<result_queue*> qs;

    virtual void _run(turn_scheduler &ts);
public:
    explicit writer_thread(safe_stream &istream, size_t block_size, std::vector<result_queue> &qs);
};


#endif //TP1_PROJECT_WRITER_THREAD_H
