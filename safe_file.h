//
// Created by Matias on 12/09/2019.
//

#ifndef TP1_PROJECT_SAFE_FILE_H
#define TP1_PROJECT_SAFE_FILE_H
#include <fstream>
#include <mutex>
#include <condition_variable>

class ProtectedFile {
    private:
    std::mutex m;
    std::condition_variable cv;
    std::fstream file;
    unsigned int access_points;
    unsigned int current_access;

    public:
    //PRE because its going to implement a round-robin system
    //it is required a number of access points or ports
    //which the file is going to iterate "openness" of
    void init(unsigned int access_points);

    //PRE attemps to open the file in path
    //POS 0 if successful
    int open(const std::string& path);

    //PRE attemps to read the file accessing through the specified port if open
    //or waiting until port is available
    //POS 0 if successfully read, -1 otherwise
    //if 0, it rotates the open port to the next one
    int read(char* buffer, size_t size,unsigned int port);

    int write(char* buffer, size_t size);

    //POS true if file reached end
    bool eof();

    //POS closes the file
    void close();

    void release();
};


#endif //TP1_PROJECT_SAFE_FILE_H
