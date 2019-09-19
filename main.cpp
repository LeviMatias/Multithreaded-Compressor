#include <iostream>
#include "safe_file.h"
#include "for_compressor.h"
#include "compressor_thread.h"
#include "writer_thread.h"
#include "safe_queue_list.h"
#include "safe_queue_template.h"
#include "result_queue.h"

int main(int argc, char* argv[]) {
    //./tp <N - #que componen bloque> <T-hreads> <Q-max q elems> <infile> <outfile>
    ProtectedFile ifile;
    ifile.open(argv[4]);
    ifile.init(1);

    int t = std::stoi(argv[2], nullptr, 10);
    int q = std::stoi(argv[3], nullptr, 10);


    std::vector<compressor_thread> threads;

    writer_thread wr(0);
    std::vector<result_queue> qs;
    for (int i=0; i<1; i++){
        qs.push_back(result_queue(t));
        threads.push_back(compressor_thread(i, &(qs.back())));
    }
    printf("asd");
    std::for_each(threads.begin(), threads.end(), [&](compressor_thread &thread){
       thread._run(ifile, 4);
    });
    //wr.run(ifile, work_qs, process_qs, 4);
    printf("2221111");
    std::for_each(threads.begin(), threads.end(), [&](compressor_thread &thread){
        printf("aaaa");
        thread.join();
        printf("bbbb");
      //  wr.join();
    });
    printf("11111111");

    printf("3");
    ifile.close();
    return 0;
}