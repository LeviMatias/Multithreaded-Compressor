//
// Created by Matias on 15/09/2019.
//

#include "compressor_thread.h"

compressor_thread::compressor_thread(safe_stream &stream, size_t block_size,\
                                result_queue &rqs) : Thread(stream, block_size){
    this->qs = &rqs;
}

void compressor_thread::_run(turn_scheduler &ts) {
    unsigned int r = 1;
    auto current_turn = std::ref(ts.get_new_turn());
    const size_t size = this->get_blk_sz() * BYTES_PER_NUMBER;
    while (r != 0){
        std::vector<char> blk(size,0);
        current_turn.get().wait_for_turn();
        r = this->get_stream()->read(&blk[0], size);
        if (r != 0){
            //read successful, lets queue again
            current_turn = std::ref(ts.finish_and_queue_again());
            blk.resize(r);
            CompressResult* res;
            //gets( or waits for) free cr
            int s = (*this->qs).get_empty(res);
            if (s == 0){
                FoRCompressor::compress(*res, blk, this->get_blk_sz());
                (*this->qs).mov_from_empty_to_ready();
            }
        } else {
            //we couldnt read, so lets leave the queue for good
            ts.finish();
        }
    }
    (*this->qs).close();
}