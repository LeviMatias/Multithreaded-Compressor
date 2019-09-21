//
// Created by Matias on 21/09/2019.
//

#include "turn_scheduler.h"

void turn_scheduler::execute_next_turn() {
    if (!this->turns.empty()){
        this->turns.front().execute();
    }
}

turn &turn_scheduler::get_new_turn() {
    this->turns.push(turn());
    return this->turns.back();
}

void turn_scheduler::finish() {
    this->turns.pop();
}

turn &turn_scheduler::finish_and_queue_again() {
    this->finish();
    return this->get_new_turn();
}

void turn_scheduler::start() {
    if (!started){
        started = true;
        execute_next_turn();
    }
}
