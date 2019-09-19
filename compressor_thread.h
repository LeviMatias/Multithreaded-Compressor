//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_COMPRESSOR_THREAD_H
#define TP1_PROJECT_COMPRESSOR_THREAD_H

#include <thread>
#include "result_queue.h"
#include "safe_file.h"
#include "for_compressor.h"
#include "safe_queue_list.h"

class compressor_thread {
    private:
    std::thread thread;
    result_queue *qs;
    int id;
    void _run(ProtectedFile &ifile, size_t block_size);
    public:

    explicit compressor_thread(int id, result_queue &qs);
    void run(ProtectedFile &ifile, size_t block_size);

    //POS calls join in the internal thread
    void join();

};


#endif //TP1_PROJECT_COMPRESSOR_THREAD_H
