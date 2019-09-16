//
// Created by Matias on 12/09/2019.
//

#include "safe_file.h"

void ProtectedFile::init(int acs_points) {
    this->access_points = acs_points;
    this->current_access = 0;
}

int ProtectedFile::open(const std::string& path){
    this->file.open(path, std::fstream::in | std::fstream::out);
    return 0;
}

int ProtectedFile::read(char* buffer, int size, int port){
    std::unique_lock<std::mutex> lock(this->m);
    while (this->current_access != port) this->cv.wait(lock);
    int s = 0;
    this->file.read(buffer, size);
    this->current_access++;
    this->current_access = this->current_access%this->access_points;
    if (this->eof()){
        s = -1;
    }
    lock.unlock();
    cv.notify_all();
    return s;
}

int ProtectedFile::write(char* buffer, int size){
    m.lock();
    this->file.write(buffer, size);
    m.unlock();
    return 0;
}

bool ProtectedFile::eof(){
    return this->file.eof();
}

void ProtectedFile::close(){
    this->file.close();
}

void ProtectedFile::release() {
    //nothing to do
}
