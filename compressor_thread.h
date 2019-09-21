//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_COMPRESSOR_THREAD_H
#define TP1_PROJECT_COMPRESSOR_THREAD_H

#include "result_queue.h"
#include "thread.h"
#include "for_compressor.h"

class compressor_thread : public Thread {
    public:
    result_queue *qs;

    virtual void _run(turn_scheduler &ts);
    public:

    explicit compressor_thread(safe_stream &strm, size_t blk_size, result_queue &qs);

};


#endif //TP1_PROJECT_COMPRESSOR_THREAD_H
