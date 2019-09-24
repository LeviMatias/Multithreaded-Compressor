//
// Created by Matias on 12/09/2019.
//

#include "safe_stream.h"
#include <string>

SafeStream::SafeStream(){
    this->ifile_opened = false;
    this->ofile_opened = false;
}

int SafeStream::OpenRead(const std::string& path){
    bool read_from_stdin = (strcmp(&path[0], "-") == 0);
    if (this->ifile_opened) CloseInput();
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

int SafeStream::OpenWrite(const std::string& path){
    bool read_from_stdin = (strcmp(&path[0], "-") == 0);
    if (this->ofile_opened) CloseOutput();
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

unsigned int SafeStream::Read(char* buffer, const unsigned int index,\
                            const size_t size){
    std::unique_lock<std::mutex> lock(this->m);
    if (this->EoF()) istream->clear();
    unsigned int s = 0;
    istream->seekg(index, std::istream::beg);
    while (s<size && (istream->read(buffer+s,1))){
        s++;
    }
    return s;
}

int SafeStream::Write(char* buffer, const size_t size){
    std::unique_lock<std::mutex> lock(this->m);
    this->ostream->write(buffer, size);
    return 0;
}

bool SafeStream::EoF(){
    return this->istream->eof();
}

void SafeStream::Close(){
    if (this->ifile_opened){
        this->ifile.close();
        this->ifile_opened = false;
    }
    if (this->ofile_opened){
        this->ofile.close();
        this->ofile_opened = false;
    }
}

SafeStream::~SafeStream(){
    this->Close();
}

void SafeStream::CloseOutput(){
    if (this->ofile_opened){
        this->ofile.close();
        this->ofile_opened = false;
    }
}

void SafeStream::CloseInput(){
    if (this->ifile_opened){
        this->ifile.close();
        this->ifile_opened = false;
    }
}

