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
    int max_elements;
    int number_of_qs;
    int current_q;
    int closed_qs;

    std::mutex m;
    std::mutex m2;
    std::condition_variable get_cv;
    std::condition_variable put_cv;
    std::vector<std::queue<CompressResult>> queues;

    public:
    void init(int number_of_queues, int max_elements);
    void add_element(int queue_id, CompressResult &result);
    CompressResult* get_element(int queue_id);
    void close_queue(int queue_id);
    bool all_queues_closed();
    void release();

};


#endif //TP1_PROJECT_SAFE_QUEUE_LIST_H
