//
// Created by Matias on 16/09/2019.
//

#ifndef TP1_PROJECT_WRITER_THREAD_H
#define TP1_PROJECT_WRITER_THREAD_H

#include <thread>
#include "safe_file.h"
#include "for_compressor.h"
#include "result_queue.h"

class writer_thread {
private:
    std::thread thread;
    const int id;
    safe_queue<result_queue> qs;

    void _run(ProtectedFile &ifile, size_t block_size);
public:
    explicit writer_thread(int id, std::vector<result_queue> *qs);
    void run(ProtectedFile &ifile, size_t block_size);
    void join();
};


#endif //TP1_PROJECT_WRITER_THREAD_H
