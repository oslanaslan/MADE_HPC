#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include "worker.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    Worker worker;

    worker.run();

    MPI_Finalize();
    return 0;
}
