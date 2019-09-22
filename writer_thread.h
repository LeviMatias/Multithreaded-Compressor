//
// Created by Matias on 16/09/2019.
//

#ifndef TP1_PROJECT_WRITER_THREAD_H
#define TP1_PROJECT_WRITER_THREAD_H

#include "safe_stream.h"
#include "compress_result.h"
#include "thread.h"
#include <vector>

class writer_thread : public Thread {
private:
    coordinated_queue<coordinated_queue<compress_result>*> qs;

    virtual void _run(turn_scheduler &ts);
public:
    explicit writer_thread(safe_stream &istream, size_t block_size,\
                        std::vector<coordinated_queue<compress_result>> &qs);
};


#endif //TP1_PROJECT_WRITER_THREAD_H
