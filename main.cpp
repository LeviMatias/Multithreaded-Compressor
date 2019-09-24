
#include "program.h"

#define EXPECTED_ARGC 5

int main(int argc, char* argv[]) {
    int t,q,n,s = (argc - 1)!=EXPECTED_ARGC;

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
    } else {
        std::cerr<<"Incorrect number of arguments: expected"\
                << EXPECTED_ARGC <<std::endl;
    }

    if (s == 0){
        s = Program::Execute(n, t, q, argv);
    }

    return s;
}
