//
// Created by Matias on 15/09/2019.
//

#include "worker_thread.h"

worker_thread::worker_thread(int id) {
    this->id = id;
}

void worker_thread::run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs) {
    int r = 0;
    while (r == 0){
        char blk[16];
        r = ifile.read(blk, 16, this->id);
        if (r == 0){
            //gets( or waits for) free cr
            CompressResult* res;
            int s = work_qs.get_element(this->id, res);
            if (s == 0){
                FoRCompressor::compress(res, blk, 16, 4);
                process_qs.add_element(this->id, *res);
            }
        }
    }
}

void worker_thread::join() {
    this->thread.join();
}
