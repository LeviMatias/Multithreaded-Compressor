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

    std::fstream ifile;
    std::fstream ofile;

    bool ifile_opened;
    bool ofile_opened;

    public:
    ~safe_stream();

    //PRE attemps to open the specified istream
    //POS 0 if successful
    //if there already was an ifile open, it closes it
    int open_read(const std::string& path);

    //PRE attemps to open the specified ostream
    //POS 0 if successful
    //if there already was an ofile open, it closes it
    int open_write(const std::string& path);

    //PRE reads from a previously successfully opened istream
    //starting from index position in the file
    //POS returns number of bytes read if s, 0 if eof reached
    unsigned int read(char* buffer, unsigned int index, size_t size);

    //PRE writes to a previously successfully opened istream
    //POS 0 if s, 1 if not
    int write(char* buffer, size_t size);

    //POS true if file reached end
    bool eof();

    //POS closes all opened files (if any)
    void close();

    //PRE a file was opened for output
    //POS closes the file
    void close_output();

    //PRE a file was opened for input
    //POS closes the file
    void close_input();
};


#endif //TP1_PROJECT_SAFE_STREAM_H
