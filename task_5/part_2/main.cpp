#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include "worker.h"
#include <cstdlib>

int main(int argc, char **argv) {
    // First argument - state line length
    int state_len = atoi(argv[1]);
    // Second argument - iteration count
    int iter_cnt = atoi(argv[2]);
    MPI_Init(&argc, &argv);
    Worker worker(state_len);

    worker.run(iter_cnt);

    MPI_Finalize();
    return 0;
}
