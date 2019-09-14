#include <iostream>
#include "protected_file.h"
#include "for_compressor.h"

int main() {
    ProtectedFile ofile;
    ofile.open("oneblk");
    FoFCompressor compressor;
    char blk[16+1] = {'\0'};
    ofile.read(blk, 16);
    CompressResult r = compressor.compress(blk, 4);
    ofile.close();
    return 0;
}