//
// Created by Matias on 16/09/2019.
//

#ifndef TP1_PROJECT_WRITER_THREAD_H
#define TP1_PROJECT_WRITER_THREAD_H

#include <thread>
#include "safe_file.h"
#include "for_compressor.h"
#include "safe_queue_list.h"

class writer_thread {
private:
    std::thread thread;
    int id;
    void _run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, size_t block_size);
public:
    explicit writer_thread(int id);
    void run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, size_t block_size);
    void join();
};


#endif //TP1_PROJECT_WRITER_THREAD_H
