#include <iostream>
#include "safe_file.h"
#include "for_compressor.h"
#include "worker_thread.h"
#include "safe_queue_list.h"

int main() {
    ProtectedFile ifile;
    ifile.open("oneblk");
    ifile.init(1);
    safe_queue_list process_qs;
    process_qs.init(1,1);
    safe_queue_list work_qs;
    work_qs.init_full(1,1);

    worker_thread w(0);
    w.run(ifile, work_qs, process_qs, 4);
    w.join();
    ifile.close();
    return 0;
}