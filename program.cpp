//
// Created by Matias on 21/09/2019.
//

#include "program.h"
#include <vector>

int Program::Execute(const int b, const int t, const int q, char **argv) {
    SafeStream istream, ostream;
    int s = 0;

    s = istream.OpenRead(argv[4]);
    if (s == 0) s = ostream.OpenWrite(argv[5]);

    if (s==0){
        std::vector<CompressorThread> threads;
        std::vector<CoordinatedQueue<CompressResult>> qs(t);

        for (int i=0; i<t; i++){
            qs[i].Init(q);
            threads.emplace_back(CompressorThread(istream, b, qs[i]));
        }
        WriterThread wr(ostream, b, qs);
        for (int i = 0; i<t; i++){
            threads[i].Run(i, t);
        }

        wr.Run(0, 1);
        for (int i = 0; i<t; i++){
            threads[i].Join();
        }
        wr.Join();

        istream.Close();
        ostream.Close();
    }
    return  s;
}
