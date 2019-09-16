//
// Created by Matias on 15/09/2019.
//

#include "worker_thread.h"

worker_thread::worker_thread(int id) {
    this->id = id;
}

void worker_thread::run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, size_t block_size){
    this->thread = std::thread(&worker_thread::_run, this, std::ref(ifile),\
    std::ref(work_qs), std::ref(process_qs), block_size);
}

void worker_thread::join() {
    this->thread.join();
}

void worker_thread::_run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, size_t block_size) {
    int r = 0;
    size_t size = block_size * BYTES_PER_NUMBER;
    while (r == 0){
        char blk[size];
        r = ifile.read(blk, size, this->id);
        if (r == 0){
            CompressResult* res;
            //gets( or waits for) free cr
            int s = work_qs.get_element(this->id, res);
            if (s == 0){
                FoRCompressor::compress(res, blk, size, block_size);
                process_qs.add_element(this->id, *res);
                work_qs.pop_element(this->id);
            }
        }
    }
    work_qs.close_queue(this->id);
}
