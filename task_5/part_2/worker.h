#ifndef WORKER
#define WORKER

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <mpi.h>
#include <exception>
#include <fstream>

class Worker {
    bool verbose;
    int rank;
    int all_state_size;
    int size;
    int state_size;
    int* states;

    void exchange_ghost_nodes();
    int state_update(int, int, int);
    void iteration_step();
    void init_state();
    void print_state(int, std::ofstream&);

public:

    Worker(int all_state_size = 200, bool verbose = true) : all_state_size(all_state_size), states(nullptr), verbose(verbose) {
        MPI_Comm_rank(MPI_COMM_WORLD, &this->rank);
        MPI_Comm_size(MPI_COMM_WORLD, &this->size);
        srand(time(NULL) + rank);
        
        // Compute current node state size. Add 2 for ghost cells
        if (all_state_size % this->size == 0) {
            this->state_size = all_state_size / this->size + 2;
        }
        else {
            if (this->rank == this->size - 1) {
                this->state_size = all_state_size % this->size + 2;
            }
            else {
                this->state_size = all_state_size / this->size + 2;
            }
        }
    }

    Worker(const Worker& other) = delete;
    void run(int);

    ~Worker() {
        delete[] this->states;
    }
};

#endif