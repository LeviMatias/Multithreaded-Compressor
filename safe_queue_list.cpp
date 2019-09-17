//
// Created by Matias on 15/09/2019.
//

#include "safe_queue_list.h"

void safe_queue_list::init(int nqueues, int max_elements) {
    this->max_elements = max_elements;
    this->number_of_qs = nqueues;
    this->closed_qs = 0;
    for (int i=0; i< nqueues; i++){
        this->queues.emplace_back(std::queue<CompressResult>());
    }
}

void safe_queue_list::init_full(int nqueues, int max_elements) {
    this->init(nqueues, max_elements);
    for (int i=0; i<nqueues; i++){
        for (int j=0; j<max_elements; j++){
            this->queues[i].push(CompressResult());
        }
    }
}

void safe_queue_list::add_element(int queue_id, CompressResult result) {
    //other option is to encapsulate q in another class that enforces limit
    std::unique_lock<std::mutex> lock(this->m2);
    while (this->queues.at(queue_id).size() == this->max_elements) {
        if (all_queues_closed()) return;
        this->put_cv.wait(lock);
    }
    this->queues.at(queue_id).push(result);
    get_cv.notify_all();
    //lock gets released by destructor
}

int safe_queue_list::get_element(int queue_id, CompressResult* &elem) {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->queues.at(queue_id).empty()) {
        if (all_queues_closed()) return 1;
        this->get_cv.wait(lock);
    }

    elem = &(this->queues.at(queue_id).front());
    return 0;
}

void safe_queue_list::pop_element(int queue_id) {
    if (!this->queues.at(queue_id).empty()){
        this->queues.at(queue_id).pop();
        put_cv.notify_all();
    }
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
