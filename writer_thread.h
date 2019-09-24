//
// Created by Matias on 16/09/2019.
//

#ifndef TP1_PROJECT_WRITER_THREAD_H
#define TP1_PROJECT_WRITER_THREAD_H

#include "safe_stream.h"
#include "compress_result.h"
#include "thread.h"
#include <vector>
#include "coordinate_queue_template.h"

class WriterThread : public Thread {
private:
    CoordinatedQueue<CoordinatedQueue<CompressResult>*> qs;

    virtual void _Run(int order, int total_threads);
public:
    explicit WriterThread(SafeStream &istream, size_t block_size,\
                        std::vector<CoordinatedQueue<CompressResult>> &qs);
};


#endif //TP1_PROJECT_WRITER_THREAD_H
