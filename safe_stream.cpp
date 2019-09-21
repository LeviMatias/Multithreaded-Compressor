//
// Created by Matias on 12/09/2019.
//

#include "safe_stream.h"

void safe_stream::init(unsigned int acs_points) {
    this->access_points = acs_points;
    this->current_access = 0;
}

int safe_stream::open_read(const std::string& path){
    bool read_from_stdin = (strcmp(&path[0], "-") == 0);
    if (read_from_stdin){
        this->istream = &std::cin;
    } else{
        file.open(path, std::fstream::in);
        if (!this->file.good()){
            printf("failed");
            return 1;
        }
        this->istream = &file;
        this->file_opened = true;
    }
    return 0;
}

int safe_stream::open_write(const std::string& path){
    bool read_from_stdin = (strcmp(&path[0], "-") == 0);
    if (read_from_stdin){
        this->ostream = &std::cout;
    } else{
        file.open(path, std::fstream::out);
        if (!this->file.good()){
            printf("failed");
            return 1;
        }
        this->ostream = &file;
        this->file_opened = true;
    }
    return 0;
}

unsigned int safe_stream::read(char* buffer, size_t size, unsigned int port) {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->current_access != port) this->cv.wait(lock);
    unsigned int s = 0;
    for (s =0; s<size && !this->eof(); s++){
        this->istream->read(buffer+s, 1);
    }

    this->current_access++;
    this->current_access = this->current_access%this->access_points;
    if (this->eof() && s>0) s--;
    lock.unlock();
    cv.notify_all();
    return s;
}

int safe_stream::write(char* buffer, size_t size){
    m.lock();
    this->file.write(buffer, size);
    m.unlock();
    return 0;
}

bool safe_stream::eof(){
    return this->istream->eof();
}

void safe_stream::close(){
    if (!this->file_opened) this->file.close();
}

void safe_stream::release() {
    //nothing to do
}
