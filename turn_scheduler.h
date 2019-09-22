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
	//POS returns a pointer to a new turn in the queue
    turn* get_new_turn();

    //PRE must be the holder of an active turn
    //POS finish turn and get a new one
    turn* finish_and_queue_again();

    //PRE must be the holder of an active turn
    //POS finish turn
    void finish();
};



#endif //TP1_PROJECT_TURN_SCHEDULER_H
