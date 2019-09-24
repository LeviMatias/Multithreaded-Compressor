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

class SafeStream {
    private:
    std::mutex m;
    std::istream*  istream;
    std::ostream* ostream;

    std::fstream ifile;
    std::fstream ofile;

    bool ifile_opened;
    bool ofile_opened;

    public:
    SafeStream();
    ~SafeStream();

    //PRE attemps to open the specified istream
    //POS 0 if successful
    //if there already was an ifile open, it closes it
    int OpenRead(const std::string& path);

    //PRE attemps to open the specified ostream
    //POS 0 if successful
    //if there already was an ofile open, it closes it
    int OpenWrite(const std::string& path);

    //PRE reads from a previously successfully opened istream
    //starting from index position in the file
    //POS returns number of bytes read if s
    // if the return value is less than size, then EoF was reached
    unsigned int Read(char* buffer, unsigned int index, size_t size);

    //PRE writes to a previously successfully opened istream
    //POS 0 if s, 1 if not
    int Write(char* buffer, size_t size);

    //PRE open an istream
    //POS true if istream reached end
    bool EoF();

    //POS closes all opened files (if any)
    void Close();

    //PRE a file was opened for output
    //POS closes the file
    void CloseOutput();

    //PRE a file was opened for input
    //POS closes the file
    void CloseInput();
};


#endif //TP1_PROJECT_SAFE_STREAM_H
