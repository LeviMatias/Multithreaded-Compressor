//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_WORKER_THREAD_H
#define TP1_PROJECT_WORKER_THREAD_H

#include <thread>
#include <list>
#include "safe_file.h"
#include "for_compressor.h"
#include "safe_queue_list.h"

class worker_thread {
    private:
    std::thread thread;
    int id;

    public:
    explicit worker_thread(int id);
    void run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, int block_size);
    void join();

};


#endif //TP1_PROJECT_WORKER_THREAD_H
