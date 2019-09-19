//
// Created by Matias on 16/09/2019.
//

#include "writer_thread.h"

writer_thread::writer_thread(int id) {
    this->id = id;
}

void writer_thread::run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, size_t block_size){
    this->thread = std::thread(&writer_thread::_run, this, std::ref(ifile),\
    std::ref(work_qs), std::ref(process_qs), block_size);
}

void writer_thread::join() {
    this->thread.join();
}

void writer_thread::_run(ProtectedFile &ofile, safe_queue_list &compress_qs,\
                        safe_queue_list &write_qs, size_t block_size) {
    int s = 0;
    while (s == 0){
        CompressResult* res;
        //gets( or waits for) free cr
        s = write_qs.get_element(this->id, res);
        if (s == 0){
            res->print_to_cout();
            //compress_qs.add_element(this->id, *res);
            //write_qs.pop_element(this->id);
        }
    }
    compress_qs.close_queue(this->id);
}
