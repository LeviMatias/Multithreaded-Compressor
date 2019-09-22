//
// Created by Matias on 15/09/2019.
//

#ifndef TP1_PROJECT_COMPRESSOR_THREAD_H
#define TP1_PROJECT_COMPRESSOR_THREAD_H

#include "thread.h"
#include "for_compressor.h"
#include <vector>

class compressor_thread : public Thread {
    private:
    coordinated_queue<compress_result> *q;
    turn* current_turn;

    virtual void _run(turn_scheduler &ts);
    
    public:
    explicit compressor_thread(safe_stream &strm, size_t blk_size,\
    coordinated_queue<compress_result> &q, turn_scheduler &ts);
};


#endif //TP1_PROJECT_COMPRESSOR_THREAD_H
