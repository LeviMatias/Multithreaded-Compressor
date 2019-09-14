//
// Created by Matias on 12/09/2019.
//

#include "protected_file.h"

int ProtectedFile::open(std::string path){
    this->file.open(path, std::fstream::in | std::fstream::out);
    return 0;
}

int ProtectedFile::read(char* buffer, int size){
    m.lock();
    this->file.read(buffer, size);
    m.unlock();
    return 0;
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
