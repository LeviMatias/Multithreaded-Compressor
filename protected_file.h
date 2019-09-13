//
// Created by Matias on 12/09/2019.
//

#ifndef TP1_PROJECT_PROTECTED_FILE_H
#define TP1_PROJECT_PROTECTED_FILE_H
#include <fstream>
#include <mutex>

class ProtectedFile {
    private:
    std::mutex m;
    std::fstream file;

    public:
    void init();
    int open(string path);
    int read(string* buffer);
    int write(string* data);
    bool eof();
    void close();
    void release();
};


#endif //TP1_PROJECT_PROTECTED_FILE_H
