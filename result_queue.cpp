//
// Created by Matias on 18/09/2019.
//

#include "result_queue.h"

result_queue::result_queue(const size_t n_elems) {
    this->empty_results.init_full(n_elems);
    this->ready_results.init(n_elems);
    this->closed = false;
}

void result_queue::close() {
    this->empty_results.close_queue();
    this->ready_results.close_queue();
    this->closed = true;
}

int result_queue::get_empty(CompressResult* &r) {
    return this->empty_results.get_element(r);;
}

void result_queue::mov_from_empty_to_ready() {
    CompressResult *r = nullptr;
    if (this->empty_results.get_element(r) == 0){
        this->ready_results.add_element(*r);
        this->empty_results.pop_element();
    }
}

int result_queue::get_ready(CompressResult* &r) {
    return this->ready_results.get_element(r);;
}

void result_queue::mov_from_ready_to_empty() {
    CompressResult *r = nullptr;
    if (this->ready_results.get_element(r) == 0){
        this->empty_results.add_element(*r);
        this->ready_results.pop_element();
    }
}

bool result_queue::is_closed() {
    return this->empty_results.is_closed() && this->ready_results.is_closed();
}

bool result_queue::is_empty_closed() {
    return this->empty_results.is_closed();
}

bool result_queue::is_ready_closed() {
    return this->ready_results.is_closed();
}

void result_queue::close_empty() {
    this->empty_results.close_queue();
}

void result_queue::close_ready() {
    this->ready_results.close_queue();
}
