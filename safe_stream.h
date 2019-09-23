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
    //PRE attemps to open the specified istream
    //POS 0 if successful
    int open_read(const std::string& path);

    //PRE attemps to open the specified ostream
    //POS 0 if successful
    int open_write(const std::string& path);

    //PRE reads from a previously successfully opened istream
    //starting from index position in the file
    //POS returns number of bytes read if s, 0 if eof reached
    unsigned int read(char* buffer, int index, size_t size);

    //PRE writes to a previously successfully opened istream
    //POS 0 if s, 1 if not
    int write(char* buffer, size_t size);

    //POS true if file reached end
    bool eof();

    //POS closes the file
    void close();

    void release();
};


#endif //TP1_PROJECT_SAFE_STREAM_H
