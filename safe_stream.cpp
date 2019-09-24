//
// Created by Matias on 12/09/2019.
//

#include "safe_stream.h"
#include <string>

int safe_stream::open_read(const std::string& path){
    bool read_from_stdin = (strcmp(&path[0], "-") == 0);
    if (this->ifile_opened) close_input();
    if (read_from_stdin){
        this->istream = &std::cin;
    } else{
        ifile.open(path, std::fstream::in | std::ios_base::binary);
        if (!this->ifile.good()){
            std::cerr<<"failed to open the input stream"<<std::endl;
            return 1;
        }
        this->istream = &ifile;
        this->ifile_opened = true;
    }
    return 0;
}

int safe_stream::open_write(const std::string& path){
    bool read_from_stdin = (strcmp(&path[0], "-") == 0);
    if (this->ofile_opened) close_output();
    if (read_from_stdin){
        this->ostream = &std::cout;
    } else{
        ofile.open(path, std::fstream::out);
        if (!this->ofile.good()){
            std::cerr<<"failed to open the output stream"<<std::endl;
            return 1;
        }
        this->ostream = &ofile;
        this->ofile_opened = true;
    }
    return 0;
}

unsigned int safe_stream::read(char* buffer, const unsigned  int index,\
                            const size_t size){
    std::unique_lock<std::mutex> lock(this->m);
    unsigned int s = 0;
    istream->seekg(index, std::ios::beg);
    for (s =0; s<size && !this->eof(); s++){
        this->istream->read(buffer+s, 1);
    }
    if (this->eof() && s>0) s--;
    return s;
}

int safe_stream::write(char* buffer, const size_t size){
    std::unique_lock<std::mutex> lock(this->m);
    this->ostream->write(buffer, size);
    return 0;
}

bool safe_stream::eof(){
    return this->istream->eof();
}

void safe_stream::close(){
    if (this->ifile_opened){
        this->ifile.close();
        this->ifile_opened = false;
    }
    if (this->ofile_opened){
        this->ofile.close();
        this->ofile_opened = false;
    }
}

safe_stream::~safe_stream(){
    this->close();
}

void safe_stream::close_output(){
    if (this->ofile_opened){
        this->ofile.close();
        this->ofile_opened = false;
    }
}

void safe_stream::close_input(){
    if (this->ifile_opened){
        this->ifile.close();
        this->ifile_opened = false;
    }
}

