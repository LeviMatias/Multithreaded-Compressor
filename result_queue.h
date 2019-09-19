//
// Created by Matias on 18/09/2019.
//

#ifndef TP1_PROJECT_RESULT_QUEUE_H
#define TP1_PROJECT_RESULT_QUEUE_H

#include "safe_queue_template.h"
#include "compress_result.h"

class result_queue {
    safe_queue<CompressResult> empty_results;
    safe_queue<CompressResult> ready_results;

public:
    explicit result_queue(size_t n_elems);

    int get_empty(CompressResult *&r);

    void mov_from_empty_to_ready();

    int get_ready(CompressResult *&r);

    void mov_from_ready_to_empty();

    void close();
};


#endif //TP1_PROJECT_RESULT_QUEUE_H
