#include <iostream>
#include "safe_file.h"
#include "for_compressor.h"
#include "compressor_thread.h"
#include "writer_thread.h"
#include "safe_queue_list.h"

int main(int argc, char* argv[]) {
    ProtectedFile ifile;
    ifile.open("oneblk");
    ifile.init(1);
    safe_queue_list process_qs;
    process_qs.init(1,1);
    safe_queue_list work_qs;
    work_qs.init_full(1,1);

    compressor_thread w(0);
    w.run(ifile, work_qs, process_qs, 4);
    writer_thread wr(0);
    wr.run(ifile, work_qs, process_qs, 4);
    w.join();
    wr.join();
    ifile.close();
    return 0;
}