//
// Created by Matias on 15/09/2019.
//

#include "compressor_thread.h"

compressor_thread::compressor_thread(int id, result_queue *rqs) {
    this->id = id;
    this->qs = rqs;
}

void compressor_thread::run(ProtectedFile &ifile, size_t block_size){
    this->thread = std::thread(&compressor_thread::_run, this, std::ref(ifile), block_size);
}

void compressor_thread::join() {
    this->thread.join();
}

void compressor_thread::_run(ProtectedFile &ifile, size_t block_size) {
    int r = 0;
    const size_t size = block_size * BYTES_PER_NUMBER;
    while (r == 0){
        std::vector<char> blk(size,0);
        r = ifile.read(&blk[0], size, this->id);
        if (r == 0){
            CompressResult* res;
            //gets( or waits for) free cr
            int s = (*this->qs).get_empty(res);
            if (s == 0){
                FoRCompressor::compress(*res, blk, block_size);
                (*this->qs).mov_from_empty_to_ready();
            }
        }
    }
    (*this->qs).close();
}
