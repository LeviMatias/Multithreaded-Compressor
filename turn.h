//
// Created by Matias on 21/09/2019.
//

#ifndef TP1_PROJECT_TURN_H
#define TP1_PROJECT_TURN_H

#include <mutex>
#include <condition_variable>

class turn {
    std::mutex m;
    std::condition_variable wait_cv;
    bool t;

public:
    turn();

    turn(const turn &other);

    //POS yields until execute is called
    void wait_for_turn();

    //POS ends the wait for turn
    //turn, now used, should be discarded
    //with the turn scheduler
    void execute();
};


#endif //TP1_PROJECT_TURN_H
