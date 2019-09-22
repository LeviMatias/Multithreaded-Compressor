//
// Created by Matias on 12/09/2019.
//

#ifndef TP1_PROJECT_SAFE_STREAM_H
#define TP1_PROJECT_SAFE_STREAM_H
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstring>
#include <string>

class safe_stream {
    private:
    std::mutex m;
    std::istream*  istream;
    std::ostream* ostream;

    std::fstream file;

    bool file_opened;
    public:

    //PRE attemps to open the file in path
    //POS 0 if successful
    int open_read(const std::string& path);

    int open_write(const std::string& path);

    //PRE attemps to read the file accessing through the specified port if open
    //or waiting until port is available
    //POS 0 if successfully read, -1 otherwise
    //if 0, it rotates the open port to the next one
    unsigned int read(char* buffer, size_t size);

    int write(char* buffer, size_t size);

    //POS true if file reached end
    bool eof();

    //POS closes the file
    void close();

    void release();


};


#endif //TP1_PROJECT_SAFE_STREAM_H
