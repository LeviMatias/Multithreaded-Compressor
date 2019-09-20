#include <iostream>
#include "safe_file.h"
#include "for_compressor.h"
#include "compressor_thread.h"
#include "writer_thread.h"
#include <stdexcept>

#define EXPECTED_ARGC 6

int execute_program(int b, int t, int q, char* argv[]){
    ProtectedFile ifile, ofile;
    bool read_from_stdin = strcmp(argv[4], "-") == 0;
    bool write_to_cout = strcmp(argv[5], "-") == 0;
    int s = 0;
    if (!read_from_stdin){
        s = ifile.open(argv[4]);
        ifile.init(t);
    }
    if (!write_to_cout){
        //create file
        {std::ofstream outfile (argv[5]);}
        s = ofile.open(argv[5]);
        ofile.init(1);//only 1 writer thread
    }
    if (s==0){
        std::vector<compressor_thread> threads;
        std::vector<result_queue> qs;

        for (int i=0; i<t; i++){
            //I need 2 separate loops because vector 3 can reposition
            //itself and break pointers inside thread
            qs.push_back(result_queue(t));
        }
        for (int i=0; i<t; i++){
            threads.push_back(compressor_thread(i, qs[i]));
        }
        writer_thread wr(0, qs);
        for (int i = 0; i<t; i++){
            threads[i].run(ifile, b, read_from_stdin);
        };

        wr.run(ofile, b, write_to_cout);
        for (int i = 0; i<t; i++){
            threads[i].join();
        };
        wr.join();

        ifile.close();
        ofile.close();
    }
    return  s;
}

int check_arguments(int argc, char* argv[]){
    //this is to set s = 0 if argc == expected_argc
    int s = argc!=EXPECTED_ARGC;
    if (s == 0){

    }


    return s;
}

int main(int argc, char* argv[]) {
    //./tp <N - #que componen bloque> <T-hreads> <Q-max q elems> <infile> <outfile>

    int t,q,n,s = argc!=EXPECTED_ARGC;

    if (s == 0) {
        try {
            n = std::stoi(argv[1], nullptr, 10);//#block size
            t = std::stoi(argv[2], nullptr, 10);//#threads
            q = std::stoi(argv[3], nullptr, 10);//#max elems
        } catch (const std::invalid_argument &ia) {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
            s = 1;
        }
        if (s == 0 && (t < 0 || q < 0 || n < 0)) s = 1;
    }

    if (s == 0){
        s = execute_program(n, t, q, argv);
    }

    return s;
}