//
// Created by Matias on 15/09/2019.
//

#include "compressor_thread.h"
#include <vector>

compressor_thread::compressor_thread(safe_stream &stream, size_t block_size,\
                    coordinated_queue<compress_result> &rq, turn_scheduler &ts)\
                    : Thread(stream, block_size){
    this->q = &rq;
    this->current_turn = ts.get_new_turn();
}

void compressor_thread::_run(turn_scheduler &ts) {
    unsigned int r = 1;
    const size_t size = this->get_blk_sz() * BYTES_PER_NUMBER;
    while (r != 0){
        std::vector<char> blk(size,0);
        current_turn->wait_for_turn();
        r = this->get_stream()->read(&blk[0], size);
        if (r != 0){
            //read successful, lets queue again
            current_turn = ts.finish_and_queue_again();
            blk.resize(r);
            compress_result res;
            FoRCompressor::compress(res, blk, this->get_blk_sz());
            (*this->q).add_element(res);
        } else {
            //we couldnt read, so lets leave the queue for good
            ts.finish();
        }
    }
    (*this->q).close_queue();
}
