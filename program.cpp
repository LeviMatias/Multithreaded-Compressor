//
// Created by Matias on 21/09/2019.
//

#include "program.h"
#include <vector>

int Program::execute(const int b, const int t, const int q, char **argv) {
    SafeStream istream, ostream;
    int s = 0;

    s = istream.open_read(argv[4]);
    if (s == 0) s = ostream.open_write(argv[5]);

    if (s==0){
        std::vector<CompressorThread> threads;
        std::vector<CoordinatedQueue<CompressResult>> qs;

        for (int i=0; i<t; i++){
            //I need 2 separate loops because vector 3 can reposition
            //itself and break pointers
            qs.emplace_back(CoordinatedQueue<CompressResult>());
            qs[i].init(q);
        }
        for (int i=0; i<t; i++){
            threads.emplace_back(CompressorThread(istream, b, qs[i]));
        }
        WriterThread wr(ostream, b, qs);
        for (int i = 0; i<t; i++){
            threads[i].run(i, t);
        }

        wr.run(0, 1);
        for (int i = 0; i<t; i++){
            threads[i].join();
        }
        wr.join();

        istream.close();
        ostream.close();
    }
    return  s;
}
