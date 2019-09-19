//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_SAFE_QUEUE_H
#define TP1_PROJECT_SAFE_QUEUE_H

#include <map>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "compress_result.h"

template <class T>
class safe_queue_list {
    private:
    unsigned int max_elements;
    bool closed;

    std::mutex m;
    std::mutex m2;
    std::condition_variable get_cv;
    std::condition_variable put_cv;

    <std::queue<T> queue;

    public:

    //[1] initializers:
    //initializes #number_of_queues each with a unique id that
    //goes from 0 to #number_of_queues-1

    //POS [1]
    void init(int max_elements);

    //POS [1]
    //also fills de queues with compress_result (could use a template)
    void init_full(int max_elements);

    //POS: adds element to queue with the queue id
    void add_element(const T &result);

    //why use poinconst ter? its possi&ble that this function
    //fails to retrieve an element when the qs are closed and thread
    //is waiting in an empty queue

    //POS: if successful elem points to element
    //0 if s -1 if not
    int get_element(T* &elem);

    //pops element in queue
    //because each thread has its own queue, no protection is needed
    void pop_element();

    void close_queue();

    //POS true when close_queue has been called once before
    bool is_closed();

    void release();

};


#endif //TP1_PROJECT_SAFE_QUEUE_H
