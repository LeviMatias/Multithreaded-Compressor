//
// Created by Matias on 15/09/2019.
//

#include "safe_queue.h"

void safe_queue::init(int max_elements) {
    this->max_elements = max_elements;
    this->closed = false;
    this->queue = std::queue<CompressResult>();
}

void safe_queue::init_full(int max_elements) {
    this->init(nqueues, max_elements);
    for (int j=0; j<max_elements; j++){
        this->queue.push(CompressResult());
    }
}

void safe_queue::add_element(const CompressResult& result) {
    std::unique_lock<std::mutex> lock(this->m2);
    while (this->queue.size() == this->max_elements) {
        if (is_closed()) return;
        this->put_cv.wait(lock);
    }
    this->queues.at(queue_id).push(result);
    get_cv.notify_all();
    //lock gets released by destructor
}

int safe_queue::get_element(CompressResult* &elem) {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->queues.empty()) {
        if (is_closed()) return 1;
        this->get_cv.wait(lock);
    }

    elem = &(this->queue.front());
    return 0;
}

void safe_queue::pop_element(int queue_id) {
    if (!this->queue.empty()){
        this->queue.pop();
        put_cv.notify_all();
    }
}


void safe_queue::close_queue() {
    this->closed = true;
    this->get_cv.notify_all();
    this->put_cv.notify_all();
}

bool safe_queue::is_closed(){
    return (this->closed);
}

void safe_queue::release() {
    //nothing to release;
}
