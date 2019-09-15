#include <iostream>
#include "protected_file.h"
#include "for_compressor.h"

int main() {
    ProtectedFile ofile;
    ofile.open("oneblk");
    FoFCompressor compressor;
    char blk[16];
    ofile.init(1);
    ofile.read(blk, 16, 0);
    CompressResult r = compressor.compress(blk, 16, 4);
    ofile.close();
    r.print_to_cout();
    return 0;
}