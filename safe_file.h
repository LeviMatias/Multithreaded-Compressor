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
    int access_points;
    int current_access;

    public:
    void init(int access_points);
    int open(const std::string& path);
    int read(char* buffer, int size, int port);
    int write(char* buffer, int size);
    bool eof();
    void close();
    void release();
};


#endif //TP1_PROJECT_SAFE_FILE_H
