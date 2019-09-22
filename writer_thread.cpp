//
// Created by Matias on 16/09/2019.
//

#include "writer_thread.h"

writer_thread::writer_thread(safe_stream &stream, size_t block_size,\
                            std::vector<coordinated_queue<compress_result>>&qs)\
                            : Thread(stream, block_size) {
    this->qs.init(qs.size());
    for (auto & q : qs){
        this->qs.add_element(&q);
    };
}

void writer_thread::_run(turn_scheduler &ts){
    int s = 0;
    //I can use is_empty without fear because this q is never added to again
    while (!this->qs.is_empty()){
       coordinated_queue<compress_result> **q;
       s = this->qs.get_element(q);
       if (s == 0){
            compress_result* res;
            s = (*q)->get_element(res);
            if (s==0){
                std::vector<char> msg;
                res->to_vector(msg);
                this->get_stream()->write(msg.data(), msg.size());
                (*q)->pop_element(); //remove the result from the list
                this->qs.move_front_to_back();
            }
        }
       if (s != 0){
            //the queue is closed so lets remove it
            qs.pop_element();
       }
    }
}
