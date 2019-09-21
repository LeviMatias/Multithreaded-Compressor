//
// Created by Matias on 21/09/2019.
//

#ifndef TP1_PROJECT_TURN_SCHEDULER_H
#define TP1_PROJECT_TURN_SCHEDULER_H

#include <queue>
#include "safe_queue_template.h"
#include "turn.h"

class turn_scheduler {
    std::queue<turn> turns;
    void execute_next_turn();
    bool started = false;

public:
    turn& get_new_turn();

    turn& finish_and_queue_again();

    void finish();

    void start();
};



#endif //TP1_PROJECT_TURN_SCHEDULER_H
