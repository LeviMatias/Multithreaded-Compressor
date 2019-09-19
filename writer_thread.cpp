//
// Created by Matias on 16/09/2019.
//

#include "writer_thread.h"

writer_thread::writer_thread(const int id, std::vector<result_queue> *qs) : id(id) {
    this->qs.init(qs->size());
    std::for_each(qs->begin(), qs->end(), [&](result_queue &q){
        this->qs.add_element(q);
    });
}

void writer_thread::run(ProtectedFile &ifile, const size_t block_size){
    this->thread = std::thread(&writer_thread::_run, this, std::ref(ifile), block_size);
}

void writer_thread::join() {
    this->thread.join();
}

void writer_thread::_run(ProtectedFile &ofile, const size_t block_size) {
    int s = -1;
    //I can use is_empty without fear because this q is never added to again
    while (s == 0 & !this->qs.is_empty()){
        CompressResult* res;
        //gets( or waits for) free cr
       // s = this->qs.get_ready(res);
        if (s == 0){
            res->print_to_cout();
            //compress_qs.add_element(this->id, *res);
            //write_qs.pop_element(this->id);
        }
    }
    //compress_qs.close_queue(this->id);
}
