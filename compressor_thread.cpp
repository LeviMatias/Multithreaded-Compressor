//
// Created by Matias on 15/09/2019.
//

#include "compressor_thread.h"

compressor_thread::compressor_thread(int id) {
    this->id = id;
}

void compressor_thread::run(ProtectedFile &ifile, safe_queue_list &work_qs,\
                        safe_queue_list &process_qs, size_t block_size){
    this->thread = std::thread(&compressor_thread::_run, this, std::ref(ifile),\
    std::ref(work_qs), std::ref(process_qs), block_size);
}

void compressor_thread::join() {
    this->thread.join();
}

void compressor_thread::_run(ProtectedFile &ifile, safe_queue_list &compress_qs,\
                        safe_queue_list &write_qs, size_t block_size) {
    int r = 0;
    const size_t size = block_size * BYTES_PER_NUMBER;
    while (r == 0){
        std::vector<char> blk(size,0);
        r = ifile.read(&blk[0], size, this->id);
        if (r == 0){
            CompressResult* res;
            //gets( or waits for) free cr
            int s = compress_qs.get_element(this->id, res);
            if (s == 0){
                FoRCompressor::compress(res, blk, size, block_size);
                write_qs.add_element(this->id, *res);
                compress_qs.pop_element(this->id);
            }
        }
    }
    write_qs.close_queue(this->id);
}
