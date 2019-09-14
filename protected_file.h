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
    int open(std::string path);
    int read(char* buffer, int size);
    int write(char* buffer, int size);
    bool eof();
    void close();
};


#endif //TP1_PROJECT_PROTECTED_FILE_H
