//
// Created by Matias on 16/09/2019.
//

#include "writer_thread.h"

writer_thread::writer_thread(safe_stream &stream, size_t block_size,\
                            std::vector<result_queue> &qs) : Thread(stream, block_size) {
    this->qs.init(qs.size());
    for (auto & q : qs){
        this->qs.add_element(&q);
    };
}

void writer_thread::_run(turn_scheduler &ts){
    int s = 0;
    //I can use is_empty without fear because this q is never added to again
    while (s == 0 && !this->qs.is_empty()){
       result_queue **q;
       s = this->qs.get_element(q);
        if (s == 0){
            CompressResult* res;
            s = (*q)->get_ready(res);
            if (s== 0){
                std::vector<char> msg;
                res->to_vector(msg);
                this->get_stream()->write(msg.data(), msg.size());
            }
            (*q)->mov_from_ready_to_empty();
            this->qs.pop_element();
            this->qs.add_element(*q);
        }
        if (s != 0){
            qs.pop_element();
        }
    }
}
