//
// Created by Matias on 18/09/2019.
//

#ifndef TP1_PROJECT_WORKER_THREAD_H
#define TP1_PROJECT_WORKER_THREAD_H


#include "thread.h"

class worker_thread: public Thread {
    worker_thread();
    void Run();
};


#endif //TP1_PROJECT_WORKER_THREAD_H
