//
// Created by Matias on 18/09/2019.
//

#ifndef TP1_PROJECT_THREAD_H
#define TP1_PROJECT_THREAD_H


#include <thread>

class Thread {
private:
    std::thread thread;

public:
    Thread () {}

    void start() {
        thread = std::thread(&Thread::run, this);
    }

    void join() {
        thread.join();
    }

    virtual void run() = 0;
    virtual ~Thread() {}
};


#endif //TP1_PROJECT_THREAD_H
