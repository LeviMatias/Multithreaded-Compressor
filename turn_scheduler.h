//
// Created by Matias on 21/09/2019.
//

#ifndef TP1_PROJECT_TURN_SCHEDULER_H
#define TP1_PROJECT_TURN_SCHEDULER_H

#include <list>
#include "coordinate_queue_template.h"
#include "turn.h"

class turn_scheduler {
    std::list<turn> turns;
    std::mutex m;
    std::mutex m2;
    void execute_next_turn();

public:
    turn* get_new_turn();

    turn* finish_and_queue_again();

    void finish();
};



#endif //TP1_PROJECT_TURN_SCHEDULER_H
