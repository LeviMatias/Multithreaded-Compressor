//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_SAFE_QUEUE_LIST_H
#define TP1_PROJECT_SAFE_QUEUE_LIST_H

#include <map>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "compress_result.h"

class safe_queue_list {
    private:
    unsigned int max_elements;
    unsigned int number_of_qs;
    unsigned int closed_qs;

    std::mutex m;
    std::mutex m2;
    std::condition_variable get_cv;
    std::condition_variable put_cv;
    //replace with map
    std::vector<std::queue<CompressResult>> queues;

    public:
    //[1] initializers:
    //initializes #number_of_queues each with a unique id that
    //goes from 0 to #number_of_queues-1

    //POS [1]
    void init(int number_of_queues, int max_elements);

    //POS [1]
    //also fills de queues with compress_result (could use a template)
    void init_full(int number_of_queues, int max_elements);

    //POS returns number of queues
    size_t get_number_of_qs();

    //POS: adds element to queue with the queue id
    void add_element(int queue_id, const CompressResult &result);

    //why use poinconst ter? its possi&ble that this function
    //fails to retrieve an element when the qs are closed and thread
    //is waiting in an empty queue

    //POS: if successful elem points to element
    //0 if s -1 if not
    int get_element(int queue_id, CompressResult* &elem);

    //pops element in queue
    //because each thread has its own queue, no protection is needed
    void pop_element(int queue_id);

    //POS increases the queue close counter by 1
    void close_queue(int queue_id);

    //POS true when #closed_qs >= #number_of_qs
    bool all_queues_closed();

    void release();

};


#endif //TP1_PROJECT_SAFE_QUEUE_LIST_H
