//
// Created by Matias on 21/09/2019.
//

#ifndef TP1_PROJECT_PROGRAM_H
#define TP1_PROJECT_PROGRAM_H

#include "safe_stream.h"
#include "compressor_thread.h"
#include "writer_thread.h"

class Program {
public:
	//executes the program
    static int execute(const int b, const int t, const int q, char* argv[]);
};


#endif //TP1_PROJECT_PROGRAM_H
