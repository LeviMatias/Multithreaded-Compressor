//
// Created by Matias on 21/09/2019.
//

#include "turn.h"

turn::turn(){
    this->t = false;
}

void turn::wait_for_turn() {
    std::unique_lock<std::mutex>lock (this->m);
    while (!this->t){
        this->wait_cv.wait(lock);
    }
    this->t = false;
}

void turn::execute(){
    this->t = true;
    this->wait_cv.notify_all();
}