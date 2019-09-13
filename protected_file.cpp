//
// Created by Matias on 12/09/2019.
//

#include "protected_file.h"

void ProtectedFile::init(){
    // nothing to init
}

int ProtectedFile::open(string path){
    this->file.open(path, std::fstream::in | std::fstream::out);
    return 0;
}

int ProtectedFile::read(string* buffer){
    m.lock();
    this->file.getline(buffer);
    m.unlock();
    return 0;
}

int ProtectedFile::write(string* data){
    m.lock();
    this->file << data;
    m.unlock();
    return 0;
}

bool ProtectedFile::eof(){
    return this->file.eof();
}

void ProtectedFile::close(){
    this->file.close();
}

void ProtectedFile::release(){
    //nothing to release
}