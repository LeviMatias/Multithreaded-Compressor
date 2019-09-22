//
// Created by Matias on 21/09/2019.
//

#include "turn_scheduler.h"

void turn_scheduler::execute_next_turn() {
    if (!this->turns.empty()){
        this->turns.front().execute();
    }
}

turn* turn_scheduler::get_new_turn(){
    std::unique_lock<std::mutex> lock(this->m);
    this->turns.push_back(turn());
    if (this->turns.size() == 1){
        execute_next_turn();
        //this is to kickstart the turn exe cycle
        //mutex protects us from exe-ing multple turns
    }
    return &this->turns.back();
}

void turn_scheduler::finish() {
    this->turns.pop_front();
    execute_next_turn();
}

turn* turn_scheduler::finish_and_queue_again() {
    std::unique_lock<std::mutex> lock(m2);
    this->finish();
    return this->get_new_turn();
}
