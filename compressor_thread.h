//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_COMPRESSOR_THREAD_H
#define TP1_PROJECT_COMPRESSOR_THREAD_H

#include "thread.h"
#include "for_compressor.h"
#include <vector>
#include "coordinate_queue_template.h"

class CompressorThread : public Thread {
    private:
    CoordinatedQueue<CompressResult> *q;

    virtual void _run(int id, int total_threads);
    
    public:
    explicit CompressorThread(SafeStream &strm, size_t blk_size,\
    CoordinatedQueue<CompressResult> &q);
};


#endif //TP1_PROJECT_COMPRESSOR_THREAD_H
