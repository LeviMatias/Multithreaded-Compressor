//
// Created by Matias on 15/09/2019.
//

#include "safe_queue_list.h"

void safe_queue_list::init(int number_of_qs, int max_elements) {
    this->max_elements = max_elements;
    this->number_of_qs = number_of_qs;
    this->current_q = 0;
    this->closed_qs = 0;
}

void safe_queue_list::add_element(int queue_id, CompressResult &result) {
    //other option is to encapsulate q in another class that enforces limit
    std::unique_lock<std::mutex> lock(this->m2);
    std::queue<CompressResult> q = this->queues[queue_id];
    while (q.size() == this->max_elements) this->put_cv.wait(lock);
    q.push(result);
    get_cv.notify_all();
    //lock gets released by destructor
}

CompressResult* safe_queue_list::get_element(int queue_id) {
    std::unique_lock<std::mutex> lock(this->m);
    std::queue<CompressResult> q = this->queues[queue_id];
    while (q.empty()) {
        if (all_queues_closed()) return nullptr;
        this->get_cv.wait(lock);
    }


    CompressResult v = q.front();
    this->queues[queue_id].pop();
    put_cv.notify_all();
    return &v;
}

void safe_queue_list::close_queue(int queue_id) {
    this->closed_qs++;
    if (all_queues_closed()){
        this->get_cv.notify_all();
    }
}

bool safe_queue_list::all_queues_closed(){
    return (this->closed_qs == this->number_of_qs);
}

void safe_queue_list::release() {
    //nothing to release;
}
