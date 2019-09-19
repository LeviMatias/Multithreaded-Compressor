#include <iostream>
#include "safe_file.h"
#include "for_compressor.h"
#include "compressor_thread.h"
#include "writer_thread.h"
#include "safe_queue_list.h"

int main(int argc, char* argv[]) {
    //./tp <N - #que componen bloque> <T-hreads> <Q-max q elems> <infile> <outfile>
    ProtectedFile ifile;
    ifile.open(argv[4]);
    ifile.init(1);

    int t = std::stoi(argv[2], nullptr, 10);
    int q = std::stoi(argv[3], nullptr, 10);

    safe_queue_list process_qs;
    process_qs.init(t,q);
    safe_queue_list work_qs;
    work_qs.init_full(t,q);
    std::vector<compressor_thread> threads;
    writer_thread wr(0);
    for (int i=0; i<t; i++){
        threads.push_back(compressor_thread(i));
    }
    std::for_each(threads.begin(), threads.end(), [&](compressor_thread &thread){
       thread.run(ifile, work_qs, process_qs, 4);
    });
    wr.run(ifile, work_qs, process_qs, 4);
    printf("2221111");
    std::for_each(threads.begin(), threads.end(), [&](compressor_thread &thread){
        printf("aaaa");
        thread.join();
        printf("bbbb");
        wr.join();
    });
    printf("11111111");

    printf("3");
    ifile.close();
    return 0;
}