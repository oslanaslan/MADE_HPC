#ifndef WORKER
#define WORKER

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <mpi.h>

class Worker {
    int rank;
    int size;
    int name;
    int known_nodes_cnt;
    int* known_nodes;
    int* known_names;
    bool verbose;

    void accept_connection();
    void connect_to_next();
    void print_known_nodes();

public:

    Worker(bool verbose = true) : known_nodes_cnt(1), known_nodes(nullptr), known_names(nullptr), verbose(verbose) {
        srand(time(NULL) + rank);
        this->name = std::rand();
        MPI_Comm_rank(MPI_COMM_WORLD, &this->rank);
        MPI_Comm_size(MPI_COMM_WORLD, &this->size);
    }

    Worker(const Worker& other) = delete;
    void run();

    ~Worker() {
        delete[] this->known_names;
        delete[] this->known_nodes;
    }
};

#endif